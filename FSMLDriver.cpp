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
