#include <iostream>
#include <cxxopts.hpp>

#include "version.h"
#include "FSMLDriver.h"
#include "FSML2CCompiler.h"

#define ERR_WRONG_ARGUMENTS		1
#define ERR_PARSING_FAILED		2
#define ERR_GRAPH_BUILD_FAILED	3

typedef struct {
	std::string input;
	bool static_factory = false;
} FSMLOptions;

FSMLOptions * ParseCmdLine(int argc, char * argv[]);
cxxopts::Options * CreateOptionsParser(std::string program_name, std::string description);
void GetOptions(cxxopts::ParseResult & result, cxxopts::Options & options, FSMLOptions & fsml_opts);
bool GetAndCheckMandatoryArguments(cxxopts::ParseResult & result, cxxopts::Options & options, FSMLOptions & fsml_opts);



int main(int argc, char * argv[])
{
	FSMLOptions * fsml_opts = nullptr;
	if ((fsml_opts = ParseCmdLine(argc, argv)) == nullptr) {
		return ERR_WRONG_ARGUMENTS;
	}

	FSMLDriver driver;
	if (driver.Parse(fsml_opts->input) == 0) {	// parsing successful
		// build FSM graph
		if (driver.BuildGraph() == false) {
			std::cerr << "[ERR] Check FSM Graph failed: " << driver.GetLastError() << std::endl;
			return ERR_GRAPH_BUILD_FAILED;
		}
		
		// translate to target language
		FSML2CCompiler c_compiler(driver);
		c_compiler.Translate();

		driver.TranslateToDOT(std::string());

		return 0;
	}

	return ERR_PARSING_FAILED;
}


FSMLOptions * ParseCmdLine(int argc, char * argv[])
{
	FSMLOptions * fsml_opts_ptr = new FSMLOptions();
	auto& fsml_opts = *fsml_opts_ptr;

	cxxopts::Options * options = CreateOptionsParser(argv[0], "Finite State Machine Language Compiler");

	options->parse_positional({"positional"});

	auto result = options->parse(argc, argv);

	GetOptions(result, *options, fsml_opts);
	if (GetAndCheckMandatoryArguments(result, *options, fsml_opts) == false) {
		delete fsml_opts_ptr;
		fsml_opts_ptr = nullptr;
	}

	return fsml_opts_ptr;
}

cxxopts::Options * CreateOptionsParser(std::string program_name, std::string description)
{
    cxxopts::Options * options = new cxxopts::Options(program_name, description);

	options->positional_help("input-file");

	options->add_options()
	("h,help", "Print this help")
	("v,version", "Print version")
	("s,static-factory", "Generate a static factory for creating FSMs")
	("positional", "input-file", cxxopts::value<std::vector<std::string>>())
	;

	return options;
}

void GetOptions(cxxopts::ParseResult & result, cxxopts::Options & options, FSMLOptions & fsml_opts)
{
	if (result.count("help")) {
		std::cout << options.help() << std::endl;
		exit(0); 
	}
	if (result.count("version")) {
		std::cout << "FSML Compiler " << FSML_VERSION << std::endl;
		exit(0);
	}
	if (result.count("static-factory")) {
		fsml_opts.static_factory = true;
	}
}

bool GetAndCheckMandatoryArguments(cxxopts::ParseResult & result, cxxopts::Options & options, FSMLOptions & fsml_opts)
{
	bool retVal = false;

	if (result.count("positional")) {
		auto positional_args = result["positional"].as<std::vector<std::string>>();
		fsml_opts.input = positional_args[0];
		retVal = true;
	}
	else {
		std::cerr << "[ERR] Missing input file" << std::endl << std::endl;
	}

	return retVal;
}
