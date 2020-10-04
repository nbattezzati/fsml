/**
 *       @file  FSMLDriver.cpp
 *      @brief  The implementation of the FSMLDriver class, i.e the parser for the Actel PDC format
 *
 * This file contains the implementation of the FSMLDriver class,
 * that offers the methods and attributes for parsing the Actel PDC format.
 *
 *     @author  Niccolo` Battezzati, niccolo.battezzati@gmail.com
 *
 *   @internal
 *     Created  01/25/11
 *     Company  Politecnico di Torino
 *   Copyright  Copyright (c) 2011, Politecnico di Torino
 *
 * This source code is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.

 * You should have received a copy of the GNU Lesser Public License
 * along with this source code.  If not, see <http://www.gnu.org/licenses/>.
 * =====================================================================================
 */

#include <string>
#include <stdio.h>

#include "FSMLDriver.h"
#include "fsml_inner.h"
#include "fsml.h"


/**
 * @brief   The FSMLDriver constructor
 * @param   edM		The EdifManager whose netlist is constrained by the Actel PDC information
 */
FSMLDriver::FSMLDriver()
{
}


/**
 * @brief   The FSMLDriver destructor
 */
FSMLDriver::~FSMLDriver()
{
}


/**
 * @brief   This method stores the C code contained in the declaration section
 * @param   c_code_block	string containing the C code block (whose curly braces will be stripped out)
 */
void FSMLDriver::Decl(const std::string & c_code_block)
{
	decl_ = c_code_block;
	// strip starting and ending curly braces
	decl_ = decl_.substr(1, decl_.size()-2);
}

/**
 * @brief   This method stores the C code contained in the time section
 * @param   c_code_block	string containing the C code block (whose curly braces will be stripped out)
 */
bool FSMLDriver::TimeSpec(const std::string & c_code_block)
{
	bool ret_val = false;

	if (periodSpec_.size() == 0) {
		timeSpec_ = c_code_block;
		// strip starting and ending curly braces
		timeSpec_ = timeSpec_.substr(1, timeSpec_.size()-2);
		ret_val = true;
	}
	else {
		lastError_ = "'period' section already defined, 'time' section cannot be defined any more";
	}

	return ret_val;
}

/**
 * @brief   This method stores the C code contained in the period section
 * @param   c_code_block	string containing the C code block (whose curly braces will be stripped out)
 */
bool FSMLDriver::PeriodSpec(const std::string & c_code_block)
{
	bool ret_val = false;

	if (timeSpec_.size() == 0) {
		periodSpec_ = c_code_block;
		// strip starting and ending curly braces
		periodSpec_ = periodSpec_.substr(1, periodSpec_.size()-2);
		ret_val = true;
	}
	else {
		lastError_ = "'time' section already defined, 'period' section cannot be defined any more";
	}

	return ret_val;
}


/**
 * @brief   This method translates the FSML grammar and creates a C code that implements the FSM
 * @param   file_name	output file name for translation (if empty translates to the default fsm.c)
 * \return	true if successfull, false if any error occurred
 */
bool FSMLDriver::translate(const std::string & file_name)
{
	bool ret_val = false;
	std::string out_file = file_name.size() > 0 ? file_name : kDefaultOutputCFile_;

	// open the output C file
	FILE * fp = fopen(out_file.c_str(), "w+");
	if (fp != nullptr) {
		fprintf(fp, "%s\n", decl_.c_str());
		ret_val = true;
	}

	// close the file
	if (fp != nullptr) {
		fclose(fp);
	}

	return ret_val;
}


/**
 * @brief   This method parses the specified Actel PDC file
 * @param   fileName	The name of the PDC file to be parsed
 * @return  0 if the parsing operation has been successful, 1 otherwise
 */
int FSMLDriver::parse(const std::string& fileName)
{
	int res;

	file = fileName;
	scanBegin();
	FSML::FSMLParser parser (*this);
#ifdef DEBUG
	parser.set_debug_level(10);
#endif
	res = parser.parse();
	scanEnd();

	return res;
}


//error handling functions
void FSMLDriver::error(const std::string& errorMsg)
{
	std::cerr << THIS_PARSER << errorMsg << std::endl;
}


void FSMLDriver::error(FSML::location const & l, const std::string& errorMsg)
{
	fprintf(stderr, "%s %s at line %d\n", \
			THIS_PARSER, \
			errorMsg.c_str(), \
			l.begin.line
	);
}
