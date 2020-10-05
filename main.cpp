#include <iostream>

#include "FSMLDriver.h"

int main(int argc, char * argv[])
{
	// TODO: check arguments
	if (argc < 1) {
		std::cerr << "Missing file name" << std::endl;
		return 1;
	}

	FSMLDriver driver;
	if (driver.Parse(argv[1]) != 0) {
		std::cerr << "Parsing failed" << std::endl;
	}
	else {
		driver.Translate(std::string());
	}

	return 0;
}
