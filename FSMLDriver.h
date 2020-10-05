/**
 *       @file  FSMLDriver.h
 *      @brief  The declaration of the FSMLDriver class, i.e the parser for the Actel PDC format
 *
 * This file contains the declaration of the FSMLDriver class,
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


#ifndef FSML_DRIVER_H_
#define	FSML_DRIVER_H_


#include <string>
#include <vector>
#include <map>

namespace FSML{
	class location;
	class FSMLParser;
}



typedef enum {
	VariableFamily_VAR,
	VariableFamily_INPUT,
	VariableFamily_OUTPUT,
} var_family_t;

class FSMVariable
{
public:	
	FSMVariable(const var_family_t family, const std::string & type, const std::string & name, const std::string & init_val)
		: family_(family), type_(type), name_(name), init_val_(init_val) {}
	virtual ~FSMVariable() {}

	inline var_family_t Family() { return family_; }
	inline std::string Type() { return type_; }
	inline std::string Name() { return name_; }
	inline std::string InitVal() { return init_val_; }

private:
	var_family_t family_;
	std::string type_;
	std::string name_;
	std::string init_val_;
};


class FSMTimer 
{
public:
	FSMTimer(const std::string & name, const std::string & init_val)
		: name_(name), init_val_(init_val) {}
	~FSMTimer() {}

	inline std::string Name() { return name_; }
	inline std::string InitVal() { return init_val_; }

private:
	std::string name_;
	std::string init_val_;
};


/**
 * @class FSMLDriver
 * @brief The FSMLDriver class implements the parsing methods for the Actel PDC format
 */
class FSMLDriver
{

public:
	//------------------ interface methods ----------------/

	//public constructor
	FSMLDriver();

	//public destructor
	virtual ~FSMLDriver();


	void Decl(const std::string & c_code_block);
	bool TimeSpec(const std::string & c_code_block);
	bool PeriodSpec(const std::string & c_code_block);
	bool AddVariable(const var_family_t f, const std::string & type, const std::string & name, const std::string & init_val);
	bool AddTimer(const std::string & name, const std::string & init_val);

	//-----------------------------------------------------/



	//------------------ compiler  methods ----------------/

	// compile and generate C code
	bool Translate(const std::string & file_name);

	std::string TranslateDecl();
	std::string TranslateTimeOrPeriod();
	std::string TranslateVariables();
	std::string TranslateTimers();

	//-----------------------------------------------------/



	//------------------ parsing methods ----------------/

	//scanner's functions	(implemented in fsml.lex)
	void scanBegin();
	void scanEnd();

	//parser's functions	
	int Parse(const std::string& fileName);
	std::string file;

	//error handling
	void error(FSML::location const & l, const std::string& m);
	void error(const std::string& errorMsg);
	inline std::string GetLastError() { return lastError_; }

	//---------------------------------------------------/
	

private:
	// code contained in the declaration section (if any)
	std::string decl_;

	// code contained in the time secction (if any)
	std::string timeSpec_;

	// code contained in the period section (if any)
	std::string periodSpec_;

	std::string lastError_;

	std::map<std::string, FSMVariable *> var_map_;
	std::map<std::string, FSMTimer *> timer_map_;
	std::string tmp_initializer_;

	const std::string kDefaultOutputCFile_ = "fsm.c";
};

	
#endif //FSML_DRIVER_H_
