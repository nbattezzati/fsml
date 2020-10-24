#include <iostream>

#include "FSMLDriver.h"
#include "FSML2CCompiler.h"

int main(int argc, char * argv[])
{
	// TODO: check arguments
	if (argc < 1) {
		std::cerr << "Missing file name" << std::endl;
		return 1;
	}

	FSMLDriver driver;
	if (driver.Parse(argv[1]) == 0) {	// parsing successful
		// build FSM graph
		if (driver.BuildGraph() == false) {
			std::cerr << "Check FSM Graph failed: " << driver.GetLastError() << std::endl;
		}
		// translate to target language
		FSML2CCompiler c_compiler(driver);
		c_compiler.Translate(std::string());

		driver.TranslateToDOT(std::string());
	}

	return 0;
}
