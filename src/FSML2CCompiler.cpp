#include <string>
#include <regex>
#include "FSML2CCompiler.h"


FSML2CCompiler::FSML2CCompiler(FSMLDriver & fsml, FSML2COptions & options, const std::string & outputName, const std::string & prefix)
	: fsml_(fsml), options_ (options)
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


std::string FSML2CCompiler::PrependFSMPointerToVarNames(std::string str, FSMLDriver & fsml_driver)
{
	std::string sub_str = str;
	std::string fsm_obj_ptr = "this->";

	// prepend FSM pointer to input/output/var variables
	for (const auto & elem : fsml_driver.VarMap()) {
		FSMVariable * v = elem.second;
		/* match all words in the input string that are equal to the name of the current variable */
		std::regex varRegex("\\b" + v->Name() + "\\b");
		/* substitute the matched variable name, prepending the FSM Object pointer */
		sub_str = std::regex_replace(sub_str, varRegex, fsm_obj_ptr+"$&");
	}

	// prepend FSM pointer to timer variables
	for (const auto & elem : fsml_driver.TimerMap()) {
		FSMTimer * v = elem.second;
		/* match all words in the input string that are equal to the name of the current variable */
		std::regex varRegex("\\b" + v->Name() + "\\b");
		/* substitute the matched variable name, prepending the FSM Object pointer */
		sub_str = std::regex_replace(sub_str, varRegex, fsm_obj_ptr+"$&");
	}

	return sub_str;
}


bool FSML2CCompiler::VarTypeIsPrimitive(std::string type)
{
	std::regex primitiveTypeRegex("\\bvoid\\b|\\bchar\\b|\\bshort\\b|\\bint\\b|\\blong\\b|\\bfloat\\b|\\bdouble\\b|\\benum\\b");
	return std::regex_match(type, primitiveTypeRegex);
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
typedef struct @PREFIX_@fsm* @PREFIX_@fsm_t;

/* built-in functions */
void @PREFIX_@fsm__reset(const @PREFIX_@fsm_t this);
@PREFIX_@state_t @PREFIX_@fsm__exec(const @PREFIX_@fsm_t this);
@PREFIX_@state_t @PREFIX_@fsm__state(const @PREFIX_@fsm_t this);
unsigned int @PREFIX_@fsm__is_in_final_state(const @PREFIX_@fsm_t this);
)";

	if (fsml_.ErrorState() != nullptr) {
		ret_str += "@PREFIX_@err_t @PREFIX_@fsm__err(const @PREFIX_@fsm_t this);\n";
	}

	ret_str += R"(
/* input setter functions */
@INPUT_FUNCTIONS@
/* output getter functions */
@OUTPUT_FUNCTIONS@

@PREFIX_@fsm_t @PREFIX_@fsm__create(void);

)";
	
	// close include guard
	ret_str += "#endif   // " + include_guard + "\n";

	// generate input setter and output getter functions
	std::string in_functions;
	std::string out_functions;
	for(const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		if (v->Family() == VariableFamily_INPUT) {
			in_functions += "void @PREFIX_@fsm__set_" + v->Name() + "(const @PREFIX_@fsm_t this, " + v->Type() + ");\n";
		}
		else if (v->Family() == VariableFamily_OUTPUT) {
			out_functions += v->Type() + " @PREFIX_@fsm__get_" + v->Name() +"(const @PREFIX_@fsm_t this);\n";
		}
	}

	// replace placeholders
	StrReplace(ret_str, "@INPUT_FUNCTIONS@", in_functions);
	StrReplace(ret_str, "@OUTPUT_FUNCTIONS@", out_functions);
	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));

	return ret_str;
}


std::string FSML2CCompiler::Translate_FSMLDecl()
{
	std::string ret_str;

	ret_str += CComment("FSML DECLARATIONS");
	
	// includes and special states definition
	if (options_.static_factory == false) {
		ret_str += "#include <stdlib.h>";		// included for malloc()
	}
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

	// timer declarations
	if (fsml_.TimerMap().size()) {
		ret_str += R"(
// timer declarations
typedef struct {
    struct timespec __started_time;
    unsigned int __timeout_ms;
} fsm_timer_t;
static void fsm_timer_start(fsm_timer_t * t);
static unsigned char fsm_timer_expired(const fsm_timer_t * t);

)";
	}
	else {
		ret_str += "\n";
	}

	// FSM object to access internal variables
	ret_str += R"(
// FSM object to access internal variables
static struct @PREFIX_@fsm {
	// state variables
	@PREFIX_@state_t __cur_state;
	@PREFIX_@state_t __next_state;
)";

	// error variable (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += "	@PREFIX_@err_t __err;\n";
	}

	// retry counters (if any)
	for (const auto & s : fsml_.UntilFirstStates()) {
		ret_str += "	unsigned int __retries_" + s->Name() + ";\n";
	}

	// variables (if any)
	ret_str += Translate_Variables();

	// timers (if any)
	ret_str += Translate_Timers();

	// close FSM object and create the 'fsm_obj' instance
	ret_str += "} fsm_obj;\n\n";


	// non-primitive-type variables initializers
	ret_str += Translate_VariableInitializers();

	// generate the factory function (according to the static-factory option)
	ret_str += R"(
@PREFIX_@fsm_t @PREFIX_@fsm__create(void)
{)";

	if (options_.static_factory == true) {
		ret_str += R"(
	@PREFIX_@fsm__reset(&fsm_obj);
	return &fsm_obj;
)";
	}
	else {
		ret_str += R"(
	@PREFIX_@fsm_t tmp_fsm = (@PREFIX_@fsm_t)malloc(sizeof(struct @PREFIX_@fsm));
	if (tmp_fsm != NULL) {
		*tmp_fsm = fsm_obj;
		@PREFIX_@fsm__reset(tmp_fsm);
	}
	else { /* malloc error, do not initialize */ }

	return tmp_fsm;
)";
	}

	// close the factory function
	ret_str += "\n}\n\n";


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
			ret_val += std::string("static struct timespec get_cur_time(void) {\n" + fsml_.TimeSpec() + "\n}\n\n\n");
		}
		else {
			ret_val += std::string("static struct timespec get_time_period(void) {\n" + fsml_.PeriodSpec() + "\n}\n\n\n");
		}
	}

	return ret_val;
}

std::string FSML2CCompiler::Translate_Variables()
{
	std::string ret_str;

	ret_str += "	// FSM variables\n";
	for (const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		ret_str += "	" + v->Type() + " " + v->Name() + ";\n";
	}

	return ret_str;
}

std::string FSML2CCompiler::Translate_VariableInitializers()
{
	std::string ret_str;

	ret_str += "	// Non-primitive-type variable initializers\n";
	for (const auto & elem : fsml_.VarMap()) {
		FSMVariable * v = elem.second;
		if (VarTypeIsPrimitive(v->Type()) == false) {
			ret_str += "static " + v->Type() + " " + v->Name() + "__initializer = " + v->InitVal() + ";\n";
		}
		else { /* no need to generate an initialzier for primitive types, they can be directly assigned in the reset function */ }
		
	}

	return ret_str;
}

std::string FSML2CCompiler::Translate_Timers()
{
	std::string ret_str;

	ret_str += "	// FSM timers\n";
	for (const auto & elem : fsml_.TimerMap()) {
		FSMTimer * v = elem.second;
		ret_str += "	" + kFsmTimerCType_ + " " + v->Name() + ";\n";
	}

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
			ret_str += "typedef " + out->Type() + " (*@PREFIX@__out_foo__" + out->Name() + ")(const @PREFIX_@fsm_t);\n";
			
			// output setter function prototypes
			for (const auto & s : fsml_.StateMap()) {
				if (s.second->DrivesOutput(out->Name())) {
					ret_str += "static " + out->Type() + " @PREFIX@__out_foo__" + out->Name() + "__" + s.second->Name() + "(const @PREFIX_@fsm_t this);\n";
				}
			}

			// output setter functions table
			ret_str += "static @PREFIX@__out_foo__" + out->Name() + " @PREFIX@__out_table__" + out->Name() + "[] = {\n";
			unsigned int cnt_states = fsml_.StateMap().size() - 1;
			for (const auto & s : fsml_.StateMap()) {
				if (s.second->DrivesOutput(out->Name())) {
					ret_str += "   @PREFIX@__out_foo__" + out->Name() + "__" + s.second->Name();
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

	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));
	StrReplace(ret_str, "@PREFIX@", prefix_);
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
					ret_str += "static " + out->Type() + " @PREFIX@__out_foo__" + out->Name() + "__" + s.second->Name() + "(const @PREFIX_@fsm_t this)\n";
					ret_str += s.second->OutputCode(out->Name()) + "\n\n";
				}
			}
		}
 	}
	ret_str += "\n";

	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));
	StrReplace(ret_str, "@PREFIX@", prefix_);
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
static void fsm_timer_start(fsm_timer_t * t)
{
   t->__started_time = get_cur_time();
}

// return 0 if timeout is not elapsed, 1 if elapsed
static unsigned char fsm_timer_expired(const fsm_timer_t * t)
{
   struct timespec now_t = get_cur_time();
   long ms_diff = (now_t.tv_nsec/1000000) - (t->__started_time.tv_nsec/1000000);
   long s_diff = (now_t.tv_sec) - (t->__started_time.tv_sec);
   double t_diff = (double)(ms_diff + s_diff*1000);

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
@PREFIX_@state_t @PREFIX_@fsm__state(const @PREFIX_@fsm_t this)
{
    return this->__cur_state;
}
)";

	// error getter function (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += R"(
// error getter function
@PREFIX_@err_t @PREFIX@__err(const @PREFIX_@fsm_t this)
{
    return this->__err;
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
			in_functions += "void @PREFIX_@fsm__set_" + v->Name() + "(const @PREFIX_@fsm_t this, " + v->Type() + " input)\n";
			in_functions += "{\n";
			in_functions += "   this->" + v->Name() + " = input;\n";
			in_functions += "}\n\n";
		}
		else if (v->Family() == VariableFamily_OUTPUT) {
			out_functions += v->Type() + " @PREFIX_@fsm__get_" + v->Name() +"(const @PREFIX_@fsm_t this)\n";
			out_functions += "{\n";
			out_functions += "   return this->" + v->Name() + ";\n";
			out_functions += "}\n\n";
		}
	}

	// replace placeholders
	StrReplace(ret_str, "@INPUT_FUNCTIONS@", in_functions);
	StrReplace(ret_str, "@OUTPUT_FUNCTIONS@", out_functions);

	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));
	StrReplace(ret_str, "@PREFIX@", prefix_);
	
	return ret_str;
}


std::string FSML2CCompiler::Translate_ResetFunction()
{
	std::string ret_str = R"(
// reset function
void @PREFIX_@fsm__reset(const @PREFIX_@fsm_t this)
{
   // init state variables
   this->__cur_state = __RESET_STATE;
   this->__next_state = __RESET_STATE;
)";

	// reset error (if any)
	if (fsml_.ErrorState() != nullptr) {
		ret_str += "	// init error variable";
		ret_str += "	this->__err = @PREFIX@Err__NoError;\n\n";
	}

	// reset timers (if any)
	if (fsml_.TimerMap().size() > 0) {
		ret_str += "	// init timers\n";
		for (const auto & timer : fsml_.TimerMap()) {
			FSMTimer * t = timer.second;
			ret_str += "	this->" + t->Name() + ".__started_time = get_cur_time();\n";
			ret_str += "	this->" + t->Name() + ".__timeout_ms = " + t->InitVal() + ";\n";
		}
		ret_str += "\n";
	}

	// reset retry variables (if any)
	if (fsml_.UntilFirstStates().size() > 0) {
		ret_str += "	// init retry variables\n";
		for (const auto & s : fsml_.UntilFirstStates()) {
			ret_str += "	this->__retries_" + s->Name() + " = 0;\n";
		}
	}

	// reset input/output/var variables (if any)
	if (fsml_.VarMap().size() > 0) {
		ret_str += "	// init FSM variables\n";
		for (const auto & elem : fsml_.VarMap()) {
			FSMVariable * v = elem.second;
			if (VarTypeIsPrimitive(v->Type())) {
				ret_str += "	this->" + v->Name() + " = " + v->InitVal() + ";\n";
			}
			else {
				// FIXME: this won't work for unions
				ret_str += "	this->" + v->Name() + " = " + v->Name() + "__initializer;\n";
			}
		}
	}


	// close function
	ret_str += "}\n\n";
	
	StrReplace(ret_str, "@PREFIX@", prefix_);
	StrReplace(ret_str, "@PREFIX_@", prefix_ + (prefix_.size() ? "_" : ""));

	return ret_str;
}


std::string FSML2CCompiler::Translate_ExecFunction()
{
	// start switch-case
	std::string ret_str = R"(
// execute function
@PREFIX_@state_t @PREFIX_@fsm__exec(const @PREFIX_@fsm_t this)
{
   // execute current state and transition evaluation
   switch(this->__cur_state) {
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
					ret_str += "         else ";
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
			ret_str += "   this->" + v->Name() + " = (@PREFIX@__out_table__" + v->Name() + "[this->__next_state] != NULL ? "
			             + "@PREFIX@__out_table__" + v->Name() + "[this->__next_state](this) : this->" + v->Name() + ");\n";
		}
	}

	// assign next state to the current one, and return
	ret_str += R"(
   // execute transition
   this->__cur_state = this->__next_state;

   return this->__cur_state;
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
unsigned int @PREFIX_@fsm__is_in_final_state(const @PREFIX_@fsm_t this)
{
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
	// remove the comma, after the last state (if any) and generate the state research code
	if (final_states_cnt) {
		final_states_array = final_states_array.substr(0, final_states_array.length()-2);

		ret_str += "    unsigned int i = 0;\n";
		ret_str += "    unsigned int final_states_length = " + std::to_string(final_states_cnt) + ";\n";
		ret_str += "    @PREFIX_@state_t final_states[] = {" + final_states_array + "};\n\n";

		ret_str += R"(
	for (i=0; i<final_states_length; ++i) { 
		if (this->__cur_state == final_states[i]) {
			return 1;
		}
	}
)";
	}

	ret_str += "    return 0;\n}\n";

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
			ret_str += "         if " + PrependFSMPointerToVarNames(t.Condition(), fsml_) + " {\n";
		break;

		case TransType_Timeout:
			ret_str += "         if (fsm_timer_expired(&this->" + t.Condition() + ")) {\n";
		break;

		case TransType_ExitUntil:
			ret_str += "         if (this->__retries_" + starting_state.Name() + " >= " + t.Condition() + ") {\n";
			ret_str += "            this->__retries_" + starting_state.Name() + " = 0;\n";
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
			ret_str += "            this->__next_state = @PREFIX@State__" + t.EndState() + ";\n";
		break;

		case TransActuator_RETRY:
			ret_str += "            this->__next_state = @PREFIX@State__" + t.EndState() + ";\n";
			ret_str += "            this->__retries_" + t.EndState() + "++;\n";
		break;

		case TransActuator_ERR:
			ret_str += "            this->__next_state = __ERR_STATE;\n";
			ret_str += "            this->__err = @PREFIX@Err__" + t.ErrorCode() + ";\n";
		break;

		default:
		break;
	}

	// start timer (if any)
	if (t.Timer().size()) {
		ret_str += "            fsm_timer_start(&this->" + t.Timer() + ");\n";
	}

	// close 'if' brace
	ret_str += "         }\n";

	return ret_str;
}