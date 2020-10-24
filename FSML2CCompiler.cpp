#include <string>
#include "FSML2CCompiler.h"


/**
 * @brief   This method translates the FSML graph and creates a C code that implements the FSM
 * @param   file_name	output file name for translation (if empty translates to the default fsm.c)
 * \return	true if successfull, false if any error occurred
 */
bool FSML2CCompiler::Translate(const std::string & file_name)
{
	bool ret_val = false;
	std::string out_file = file_name.size() > 0 ? file_name : kDefaultOutputCFile_;

	// open the output C file
	FILE * fp = fopen(out_file.c_str(), "w+");
	if (fp != nullptr) {

		fprintf(fp, "%s", Translate_FSMLDecl().c_str());
		fprintf(fp, "%s", Translate_Decl().c_str());
		fprintf(fp, "%s", Translate_TimeOrPeriod().c_str());
		fprintf(fp, "%s", Translate_Variables().c_str());
		fprintf(fp, "%s", Translate_Timers().c_str());
		
		ret_val = true;
	}

	// close the file
	if (fp != nullptr) {
		fclose(fp);
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