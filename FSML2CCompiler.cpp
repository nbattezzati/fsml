#include <string>
#include <algorithm>
#include "FSML2CCompiler.h"


FSML2CCompiler::FSML2CCompiler(FSMLDriver & fsml, const std::string & outputName, const std::string & prefix)
	: fsml_(fsml)
{
	std::string fsmName = fsml.FsmName();
	std::transform(fsmName.begin(), fsmName.end(), fsmName.begin(), std::toupper);

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
			fprintf(fp, "%s", Translate_FSMLDecl().c_str());
			fprintf(fp, "%s", Translate_Decl().c_str());
			fprintf(fp, "%s", Translate_TimeOrPeriod().c_str());
			fprintf(fp, "%s", Translate_Variables().c_str());
			fprintf(fp, "%s", Translate_Timers().c_str());
			
			ret_val = true;
		}

		// close the .c file
		if (fp != nullptr) {
			fclose(fp);
		}
	}

	return ret_val;
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
	ret_str += "typedef struct {\n";
	ret_str += "   " + prefix_ + (prefix_.size() ? "_" : "") + "state_t (*state)(void);\n";
	ret_str += "   " + prefix_ + (prefix_.size() ? "_" : "") + "err_t (*err)(void);\n";
	ret_str += "   void (*reset)(void);\n";
	ret_str += "   " + prefix_ + (prefix_.size() ? "_" : "") + "state_t (*run)(void);\n";
	ret_str += "} " + prefix_ + (prefix_.size() ? "_" : "") + "fsm_t;\n\n";
	ret_str += "extern " + prefix_ + (prefix_.size() ? "_" : "") + "fsm_t * " + prefix_ + (prefix_.size() ? "_" : "") + "fsm;\n\n";

	// close include guard
	ret_str += "#endif   // " + include_guard + "\n";

	return ret_str;
}

std::string FSML2CCompiler::Translate_FSMLDecl()
{
	std::string ret_val;
	ret_val += CComment("FSML declarations");
	ret_val += "#include <time.h>\n";
	ret_val += "\n\n";
	return ret_val;
}

std::string FSML2CCompiler::Translate_Decl()
{
	std::string ret_val;
	ret_val += CComment("User declarations");
	ret_val += std::string(fsml_.Decl() + "\n\n");
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