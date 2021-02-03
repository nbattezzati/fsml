#include <string>
#include "FSML2CCompiler.h"


FSML2CCompiler::FSML2CCompiler(FSMLDriver & fsml, const std::string & outputName, const std::string & prefix)
	: fsml_(fsml)
{
	std::string fsmName = fsml.FsmName();

	outputName_ = (outputName.size() ? outputName : fsmName) + "_fsm";
	prefix_ = prefix.size() ? prefix : fsmName;
}


/**
 * @brief   This method translates the FSML graph and creates a C code that implements the FSM
 * \return	true if successfull, false if any error occurred
 */
bool FSML2CCompiler::Translate()
{
	bool ret_val = false;

	// open the output .h file
	FILE * fp = fopen(std::string(outputName_ + ".h").c_str(), "w+");
	if (fp != nullptr) {
		// translate H
		fprintf(fp, "%s", Generate_Header().c_str());

		// close the .h file
		fclose(fp);

		// open the output .c file
		fp = fopen(std::string(outputName_ + ".c").c_str(), "w+");
		if (fp != nullptr) {
			// translate C
			fprintf(fp, "%s", Translate_Decl().c_str());
			fprintf(fp, "%s", Translate_FSMLDecl().c_str());
			fprintf(fp, "%s", Translate_TimeOrPeriod().c_str());
			fprintf(fp, "%s", Translate_Variables().c_str());
			fprintf(fp, "%s", Translate_Timers().c_str());
			fprintf(fp, "%s", Translate_OutputDeclarations().c_str());
			fprintf(fp, "%s", Translate_OutputFunctions().c_str());
			fprintf(fp, "%s", Translate_TimerFunctions().c_str());
			fprintf(fp, "%s", Translate_GetterFunctions().c_str());
			fprintf(fp, "%s", Translate_ResetFunction().c_str());
			fprintf(fp, "%s", Translate_ExecFunction().c_str());
			fprintf(fp, "%s", Translate_IsInFinalStateFunction().c_str());
			
			ret_val = true;
		}

		// close the .c file
		if (fp != nullptr) {
			fclose(fp);
		}
	}

	return ret_val;
}


std::string & FSML2CCompiler::StrReplace(std::string & str, std::string toReplace, std::string replaceWith)
{
	std::string::size_type n = std::string::npos;

	while((n = str.find(toReplace)) != std::string::npos) {
		str.replace(n, toReplace.length(), replaceWith);
	}
	return str;
}


std::string FSML2CCompiler::CComment(const std::string & msg)
{
	std::string comment;
	comment += "/";
	for(int i=0; i<kCCommentWidth_; ++i) { comment += "*"; }
	comment += "/\n";

	comment += "/*";
	for (int i=0; i<(kCCommentWidth_-1-msg.length())/2; ++i) { comment += " "; }
	comment += msg;
	for (int i=0; i<(kCCommentWidth_-1-msg.length())/2; ++i) { comment += " "; }
	comment += "*/\n";

	comment += "/";
	for(int i=0; i<kCCommentWidth_; ++i) { comment += "*"; }
	comment += "/\n";

	return comment;
}

std::string FSML2CCompiler::Generate_Header()
{
	std::string ret_str;

	// include guard
	std::string include_guard = "__" + prefix_ + (prefix_.size() ? "_" : "") + "FSM_H__";
	ret_str += "#ifndef " + include_guard + "\n";
	ret_str += "#define " + include_guard + "\n\n";

	// user exports
	ret_str += Translate_Export();

	// states enum
	ret_str += CComment("STATES");
	ret_str += "typedef enum {\n";
	for (const auto & elem : fsml_.StateMap()) {
		FSMState * s = elem.second;
		ret_str += "   " + prefix_ + "State__" + s->Name() + ",\n";
	}
	ret_str += "} " + prefix_ + (prefix_.size() ? "_" : "") + "state_t;\n\n";

	// errors enum
	if (fsml_.ErrorState() != nullptr) {
		ret_str += CComment("ERRORS");
		ret_str += "typedef enum {\n";
		ret_str += "   " + prefix_ + "Err__NoError,\n";
		for (const auto & elem : fsml_.ErrorMap()) {
			std::string e = elem.first;
			ret_str += "   " + prefix_ + "Err__" + e + ",\n";
		}
		ret_str += "} " + prefix_ + (prefix_.size() ? "_" : "") + "err_t;\n\n";
	}

	// FSM structure
	ret_str += CComment("FSM STRUCTURE");
	ret_str += R"(
typedef struct {
   /* built-in functions */
   void (*reset)(void);
   @PREFIX_@state_t (*exec)(void);
   @PREFIX_@state_t (*state)(void);
   unsigned int (*is_in_final_state)(void);
)";

	if (fsml_.ErrorState() != nullptr) {
		ret_str += "   @PREFIX_@err_t (*err)(void);\n";
	}

	ret_str += R"(
   /* input setter functions */
@INPUT_FUNCTIONS@
   /* output getter functions */
@OUTPUT_FUNCTIONS@
} @PREFIX_@fsm_t;

extern const @PREFIX_@fsm_t * @PREFIX_@fsm;

)";
	
	// close include guard
	ret_str += "#endif   // " + include_guard + "\n";

	// generate input setter and output getter functions
	std::string in_functions;
	std::string out_functions;
	for(const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		if (v->Family() == VariableFamily_INPUT) {
			in_functions += "   void (* set_" + v->Name() + ")(" + v->Type() + ");\n";
		}
		else if (v->Family() == VariableFamily_OUTPUT) {
			out_functions += "   " + v->Type() + " (* get_" + v->Name() +")(void);\n";
		}
	}

	// replace placeholders
	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));
	StrReplace(ret_str, "@INPUT_FUNCTIONS@", in_functions);
	StrReplace(ret_str, "@OUTPUT_FUNCTIONS@", out_functions);

	return ret_str;
}


std::string FSML2CCompiler::Translate_FSMLDecl()
{
	std::string ret_str;

	ret_str += CComment("FSML DECLARATIONS");
	
	// includes and special states definition
	ret_str += R"(
#include <stddef.h>
#include <time.h>
#include "@OUTPUT_NAME@.h"

// special states definition
#define __RESET_STATE   @PREFIX@State__@RESET_STATE@
)";

	// define error state (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += "#define __ERR_STATE   @PREFIX@State__" + fsml_.ErrorState()->Name() + "\n";
	}

	// private variables
	ret_str += R"(
// private variables
static @PREFIX_@state_t __cur_state;
static @PREFIX_@state_t __next_state;
)";

	// error variable (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += "static @PREFIX_@err_t __err;\n";
	}

	// retry counters (if any)
	for (const auto & s : fsml_.UntilFirstStates()) {
		ret_str += "static unsigned int __retries_" + s->Name() + ";\n";
	}

	// public function declarations
	ret_str += R"(
// public function declarations
@PREFIX_@state_t __get_state(void);
)";
	// error getter (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += "@PREFIX_@err_t __get_err(void);\n";
	}

	ret_str += R"(
void __reset(void);
@PREFIX_@state_t __exec(void);
unsigned int __is_in_final_state(void);
)";

	// input setter and output getter functions
	std::string in_functions;
	std::string out_functions;
	unsigned int cnt_inout_functions = 0;
	for(const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		if (v->Family() == VariableFamily_INPUT) {
			in_functions += "void __set_" + v->Name() + "(" + v->Type() + ");\n";
			cnt_inout_functions++;
		}
		else if (v->Family() == VariableFamily_OUTPUT) {
			out_functions += v->Type() + " __get_" + v->Name() +"(void);\n";
			cnt_inout_functions++;
		}
		else { /* not an IN/OUT variable */ }
	}

	ret_str += "// input setter and output getter functions\n";
	ret_str += in_functions;
	ret_str += out_functions;
	ret_str += "\n";

	// FSM object to access internal variables
	ret_str += R"(
// FSM object to access internal variables
static @PREFIX_@fsm_t this = {
    .state = __get_state,
)";
	if (fsml_.ErrorState() != nullptr) {
		ret_str += "    .err = __get_err,\n";
	}
	ret_str += R"(
    .reset = __reset,
    .exec = __exec,
	.is_in_final_state = __is_in_final_state,
)";

	// add input/output functions
	unsigned int cnt_functions = 0;
	for(const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		if (v->Family() == VariableFamily_INPUT) {
			ret_str += "   .set_" + v->Name() + " = __set_" + v->Name();
			cnt_functions++;
		}
		else if (v->Family() == VariableFamily_OUTPUT) {
			ret_str += "   .get_" + v->Name() + " = __get_" + v->Name();
			cnt_functions++;
		}
		else { /* not an IN/OUT variable */ }
		
		// add comma at the end of the line
		if (v->Family() == VariableFamily_INPUT || v->Family() == VariableFamily_OUTPUT) {
			if (cnt_functions < cnt_inout_functions) {
				ret_str += ",";
			}
			ret_str += "\n";
		}
	}

	// close FSM object
	ret_str += R"(
};
const @PREFIX_@fsm_t * @PREFIX_@fsm = &this;
)";

	// timer declarations
	if (fsml_.TimerMap().size()) {
		ret_str += R"(
// timer declarations
typedef struct {
    struct timespec __started_time;
    unsigned int __timeout_ms;
} fsm_timer_t;
void fsm_timer_start(fsm_timer_t * t);
unsigned char fsm_timer_expired(fsm_timer_t * t);

)";
	}
	else {
		ret_str += "\n";
	}

	// replace placeholders
	StrReplace(ret_str, "@OUTPUT_NAME@", outputName_);
	StrReplace(ret_str, "@RESET_STATE@", fsml_.ResetState()->Name());
	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));
	StrReplace(ret_str, "@PREFIX@", prefix_);

	return ret_str;
}

std::string FSML2CCompiler::Translate_Decl()
{
	std::string ret_val;
	ret_val += CComment("User declarations");
	ret_val += std::string(fsml_.Decl() + "\n\n");
	return ret_val;
}

std::string FSML2CCompiler::Translate_Export()
{
	std::string ret_val;
	ret_val += CComment("User exports");
	ret_val += std::string(fsml_.Export() + "\n\n");
	return ret_val;
}

std::string FSML2CCompiler::Translate_TimeOrPeriod()
{
	std::string ret_val;

	if (!fsml_.TimerMap().empty()) {
		ret_val += CComment("Timeout handling");
		if (fsml_.TimeSpec().size() > 0) {
			ret_val += std::string("struct timespec get_cur_time(void) {\n" + fsml_.TimeSpec() + "\n}\n\n\n");
		}
		else {
			ret_val += std::string("struct timespec get_time_period(void) {\n" + fsml_.PeriodSpec() + "\n}\n\n\n");
		}
	}

	return ret_val;
}

std::string FSML2CCompiler::Translate_Variables()
{
	std::string ret_str;

	ret_str += CComment("FSM variables");
	for (const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		ret_str += kStaticCKeyword_ + " " + v->Type() + " " + v->Name() + " = " + v->InitVal() + ";\n";
	}
	ret_str += "\n\n";

	return ret_str;
}

std::string FSML2CCompiler::Translate_Timers()
{
	std::string ret_str;

	ret_str += CComment("FSM timers");
	for (const auto & elem : fsml_.TimerMap()) {
		FSMTimer * v = elem.second;
		ret_str += kStaticCKeyword_ + " " + kFsmTimerCType_ + " " + v->Name() + ";\n";
	}
	ret_str += "\n\n";

	return ret_str;
}

std::string FSML2CCompiler::Translate_OutputDeclarations()
{
	std::string ret_str;

	ret_str += CComment("Output functions");

	// loop over all output variables
	for (const auto & v : fsml_.VarMap()) {
		if (v.second->Family() == VariableFamily_OUTPUT) {
			FSMVariable * out = v.second;

			// output setter function
			ret_str += "// OUT Variable: " + out->Name() + ";\n";
			ret_str += "typedef " + out->Type() + " (*__out_foo__" + out->Name() + ")(void);\n";
			
			// output setter function prototypes
			for (const auto & s : fsml_.StateMap()) {
				if (s.second->DrivesOutput(out->Name())) {
					ret_str += out->Type() + " __out_foo__" + out->Name() + "__" + s.second->Name() + "(void);\n";
				}
			}

			// output setter functions table
			ret_str += "static __out_foo__" + out->Name() + " __out_table__" + out->Name() + "[] = {\n";
			unsigned int cnt_states = fsml_.StateMap().size() - 1;
			for (const auto & s : fsml_.StateMap()) {
				if (s.second->DrivesOutput(out->Name())) {
					ret_str += "   __out_foo__" + out->Name() + "__" + s.second->Name();
				}
				else {
					ret_str += "   NULL";
				}
				// add comma if this is not the last table entry
				if (cnt_states > 0) {
					ret_str += ",";
				}
				cnt_states--;
				ret_str += "\n";
			}
			ret_str += "};\n\n";
		}
 	}

	return ret_str;
}


std::string FSML2CCompiler::Translate_OutputFunctions()
{
	std::string ret_str;

	// loop over all output variables
	for (const auto & v : fsml_.VarMap()) {
		if (v.second->Family() == VariableFamily_OUTPUT) {
			FSMVariable * out = v.second;

			// output setter functions
			ret_str += "// OUT Variable: " + out->Name() + ";\n";
			
			// output setter function prototypes
			for (const auto & s : fsml_.StateMap()) {
				if (s.second->DrivesOutput(out->Name())) {
					ret_str += out->Type() + " __out_foo__" + out->Name() + "__" + s.second->Name() + "(void)\n";
					ret_str += s.second->OutputCode(out->Name()) + "\n\n";
				}
			}
		}
 	}
	ret_str += "\n";

	return ret_str;
}


std::string FSML2CCompiler::Translate_TimerFunctions()
{
	std::string ret_str;
	
	if (fsml_.TimerMap().size() == 0) {
		return ret_str;
	}

	ret_str += CComment("Timer functions");
	
	ret_str += R"(
void fsm_timer_start(fsm_timer_t * t)
{
   t->__started_time = get_cur_time();
}

// return 0 if timeout is not elapsed, 1 if elapsed
unsigned char fsm_timer_expired(fsm_timer_t * t)
{
   struct timespec now_t = get_cur_time();
   long ms_diff = now_t.tv_nsec/1000000 - t->__started_time.tv_nsec/1000000;
   long s_diff = now_t.tv_sec - t->__started_time.tv_sec;
   double t_diff = ms_diff + s_diff*1000;

   return t_diff >= t->__timeout_ms;
}

)";

	return ret_str;
}


std::string FSML2CCompiler::Translate_GetterFunctions()
{
	std::string ret_str = CComment("Public functions");
	
	ret_str += R"(
// state getter function
@PREFIX_@state_t __get_state(void)
{
    return __cur_state;
}
)";

	// error getter function (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += R"(
// error getter function
@PREFIX_@err_t __get_err(void)
{
    return __err;
}
)";
	}

	ret_str += R"(
// input setter functions
@INPUT_FUNCTIONS@
// output getter functions
@OUTPUT_FUNCTIONS@
)";

	// input setter / output getter public functions
	// generate input setter and output getter functions
	std::string in_functions;
	std::string out_functions;
	for(const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		if (v->Family() == VariableFamily_INPUT) {
			in_functions += "void __set_" + v->Name() + "(" + v->Type() + " input)\n";
			in_functions += "{\n";
			in_functions += "   " + v->Name() + " = input;\n";
			in_functions += "}\n\n";
		}
		else if (v->Family() == VariableFamily_OUTPUT) {
			out_functions += v->Type() + " __get_" + v->Name() +"(void)\n";
			out_functions += "{\n";
			out_functions += "   return " + v->Name() + ";\n";
			out_functions += "}\n\n";
		}
	}

	// replace placeholders
	StrReplace(ret_str, "@INPUT_FUNCTIONS@", in_functions);
	StrReplace(ret_str, "@OUTPUT_FUNCTIONS@", out_functions);

	return StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));
}


std::string FSML2CCompiler::Translate_ResetFunction()
{
	std::string ret_str = R"(
// reset function
void __reset(void)
{
   // init private variables
   __cur_state = __RESET_STATE;
   __next_state = __RESET_STATE;
)";

	// reset error (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += "   __err = @PREFIX@Err__NoError;\n\n";
	}


	// reset timers (if any)
	if (fsml_.TimerMap().size() > 0) {
		ret_str += "   // init timers\n";
		for (const auto & timer : fsml_.TimerMap()) {
			FSMTimer * t = timer.second;
			ret_str += "   " + t->Name() + ".__started_time = get_cur_time();\n";
			ret_str += "   " + t->Name() + ".__timeout_ms = " + t->InitVal() + ";\n";
		}
		ret_str += "\n";
	}

	// retry variables (if any)
	if (fsml_.UntilFirstStates().size() > 0) {
		ret_str += "   // init retry variables\n";
		for (const auto & s : fsml_.UntilFirstStates()) {
			ret_str += "   __retries_" + s->Name() + " = 0;\n";
		}
	}

	// close function
	ret_str += "}\n\n";
	
	return StrReplace(ret_str, "@PREFIX@", prefix_);
}


std::string FSML2CCompiler::Translate_ExecFunction()
{
	// start switch-case
	std::string ret_str = R"(
// execute function
@PREFIX_@state_t __exec(void)
{
   // execute current state and transition evaluation
   switch(__cur_state) {
)";

	// loop over the states
	for (const auto & elem : fsml_.StateMap()) {
		FSMState * s = elem.second;
		// start case
		ret_str += "      case @PREFIX@State__" + s->Name() + ":\n";
		ret_str += "      {\n";
		
		// user defined code (if any)
		if (s->Code().size() > 0) {
			ret_str += "         " + s->Code() + "\n";
		}

		bool first_trans_done = false;
		// retry transition (if any)
		for (const auto & t : s->Transitions()) {
			if (t->Type() == TransType_ExitUntil) {
				ret_str += TranslateTransition(*s, *t);
				first_trans_done = true;
			}
		}

		// all other thransitions
		for (const auto & t : s->Transitions()) {
			if (t->Type() != TransType_ExitUntil) {
				if (first_trans_done == true) {
					ret_str += "         else\n";
				}
				ret_str += TranslateTransition(*s, *t);
				first_trans_done = true;
			}
		}

		// else remain in this state (if any transition has been put before)
		if (first_trans_done) {
			ret_str += R"(
         else {
	        // stay in this state
		 }
)";
		}

		// end case
		ret_str += R"(
      }
      break;

)";   
	}

	// end switch-case
	ret_str += R"(
      default:
	     // TODO: handle error here
      break;
   }
)";

	// assign output values (if any)
	ret_str += "   // assign new values to the output (Mealy Machine)\n";
	for(const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		if (v->Family() == VariableFamily_OUTPUT) {
			ret_str += "   " + v->Name() + " = (__out_table__" + v->Name() + "[__next_state] != NULL ? "
			             + "__out_table__" + v->Name() + "[__next_state]() : " + v->Name() + ");\n";
		}
	}

	// assign next state to the current one, and return
	ret_str += R"(
   // execute transition
   __cur_state = __next_state;

   return __cur_state;
}
)";

	StrReplace(ret_str, "@PREFIX@", prefix_);
	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));
	
	return ret_str;
}


std::string FSML2CCompiler::Translate_IsInFinalStateFunction()
{
	std::string ret_str = R"(
// is_in_final_state function
unsigned int __is_in_final_state(void)
{
	unsigned int i = 0;
)";

	// generate the array of final state codes
	std::string final_states_array = "";
	unsigned int final_states_cnt = 0;
	for (auto const & s :fsml_.StateMap()) {
		if(s.second->HasType(kStateTypeEnd)) {
			final_states_array += "@PREFIX@State__" + s.second->Name() + ", ";
			final_states_cnt++;
		}
	}
	// remove the comma, after the last state (if any)
	if (final_states_cnt) {
		final_states_array = final_states_array.substr(0, final_states_array.length()-2);
	}

	ret_str += "    unsigned int final_states_length = " + std::to_string(final_states_cnt) + ";\n";
	ret_str += "    @PREFIX_@state_t final_states[] = {" + final_states_array + "};\n\n";

	ret_str += R"(
	for (i=0; i<final_states_length; ++i) { 
		if (__cur_state == final_states[i]) {
			return 1;
		}
	}
	return 0;
}
)";

	StrReplace(ret_str, "@PREFIX@", prefix_);
	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));

	return ret_str;
}



std::string FSML2CCompiler::TranslateTransition(FSMState & starting_state, FSMTransition & t)
{
	std::string ret_str;

	// transition condition
	switch(t.Type()) {
		case TransType_Normal:
			ret_str += "         if " + t.Condition() + " {\n";
		break;

		case TransType_Timeout:
			ret_str += "         if (fsm_timer_expired(&" + t.Condition() + ")) {\n";
		break;

		case TransType_ExitUntil:
			ret_str += "         if (__retries_" + starting_state.Name() + " >= " + t.Condition() + ") {\n";
			ret_str += "            __retries_" + starting_state.Name() + " = 0;\n";
		break;

		default:
		break;
	}

	// transition code
	if (t.Code().size()) {
		ret_str += "            " + t.Code() + "\n";
	}

	// transition actuator actions
	switch(t.Actuator()) {
		case TransActuator_GO:
			ret_str += "            __next_state = @PREFIX@State__" + t.EndState() + ";\n";
		break;

		case TransActuator_RETRY:
			ret_str += "            __next_state = @PREFIX@State__" + t.EndState() + ";\n";
			ret_str += "            __retries_" + t.EndState() + "++;\n";
		break;

		case TransActuator_ERR:
			ret_str += "            __next_state = __ERR_STATE;\n";
			ret_str += "            __err = @PREFIX@Err__" + t.ErrorCode() + ";\n";
		break;

		default:
		break;
	}

	// start timer (if any)
	if (t.Timer().size()) {
		ret_str += "            fsm_timer_start(&" + t.Timer() + ");\n";
	}

	// close 'if' brace
	ret_str += "         }\n";

	return ret_str;
}