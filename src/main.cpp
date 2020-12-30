#include <iostream>

#include "FSMLDriver.h"
#include "FSML2CCompiler.h"

#define ERR_WRONG_ARGUMENTS		1
#define ERR_PARSING_FAILED		2
#define ERR_GRAPH_BUILD_FAILED	3

int main(int argc, char * argv[])
{
	// TODO: check arguments
	if (argc < 1) {
		std::cerr << "[ERR] Missing file name" << std::endl;
		return ERR_WRONG_ARGUMENTS;
	}

	FSMLDriver driver;
	if (driver.Parse(argv[1]) == 0) {	// parsing successful
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
