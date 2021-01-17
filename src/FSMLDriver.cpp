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
#include <algorithm>
#include <stdio.h>

#include "FSMLDriver.h"
#include "fsml_inner.h"
#include "fsml.h"

bool FSMState::AddType(state_type_t type) 
{
	bool ret_val = false;

	// if this is a reset/error type and there is already one in the driver, set an error
	if ((type == kStateTypeReset) && (driver_.ResetState() != nullptr)) {
		driver_.SetLastError("'reset' state already defined");
	}
	else if ((type == kStateTypeErr) && (driver_.ErrorState() != nullptr)) {
		driver_.SetLastError("'err' state already defined");
	}
	
	// otherwise add the type 
	else {
		types_.push_back(type);
		ret_val = true;
	}

	return ret_val;
}

bool FSMState::HasType(state_type_t type)
{
	auto res = std::find_if(
		types_.begin(), types_.end(), 
		[&type](const state_type_t elem){ return elem == type; }
	); 
	return res != types_.end();
}

bool FSMState::AddOutput(const std::string & output, const std::string & out_code)
{
	if (driver_.varExists(output) == true) {
		if (output_map_.find(output) == output_map_.end()) {
			output_map_[output] = out_code;
			return true;
		}
		else {
			driver_.SetLastError("Output <" + output + "> redeclared in state <" + name_ + ">");
		}
	}
	else {
		driver_.SetLastError("State <" + name_ + "> tries to set inexistent output <" + output + ">");
	}

	return false;
}

bool FSMState::SetEndStateForRetryTrans(FSMState * s)
{
	bool retry_exists = false;
	for(FSMTransition * t : transitions_) {
		if (t->Actuator() == TransActuator_RETRY) {
			t->EndState(s->Name());
			retry_exists = true;
		}
	}

	return retry_exists;
}



bool FSMTransition::CheckCondition()
{
	bool ret_val = false;

	switch (type_) {
		case TransType_Normal:
		case TransType_ExitUntil:
			// TODO: implement checks on condition
			ret_val = true;
		break;

		case TransType_Timeout:
			ret_val = driver_.TimerExists(condition_);
		break;

		default:
		break;
	}

	return ret_val;
}

bool FSMTransition::CheckDestination()
{
	switch(actuator_) {
		case TransActuator_GO: 
			if (driver_.StateExists(endState_) == false) {
				return false;
			}
		break;

		case TransActuator_ERR: 
		{	
			FSMState * err = driver_.ErrorState();
			if (err == nullptr) {
				return false;
			}
			// set the end state name on the transition
			endState_ = err->Name();
		}
		break;
		
		// TODO: should never happen since it should be translated into a GO or ERR actuator
		case TransActuator_RETRY: break;
	}

	return true;
}


bool FSMTransition::SetTimer(const std::string & timer)
{
	// check if the timer exists
	if (driver_.TimerExists(timer)) {
		timer_ = timer;
		return true;
	}
	// return error otherwise
	driver_.SetLastError("timer <" + timer + "> is not defined");
	return false;
}


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
	// TODO: empty tha maps
	// TODO: delete states
}


/**
 * @brief   This method stores the C code contained in the declaration section
 * @param   c_code_block	string containing the C code block (whose curly braces will be stripped out)
 */
bool FSMLDriver::Decl(const std::string & c_code_block)
{
	bool ret_val = false;

	if (decl_.length() == 0) {
		decl_ = c_code_block;
		// strip starting and ending curly braces
		decl_ = decl_.substr(1, decl_.size()-2);
		ret_val = true;
	}
	else {
		lastError_ = "'decl' section already defined";
	}

	return ret_val;
}


/**
 * @brief   This method stores the C code contained in the export section
 * @param   c_code_block	string containing the C code block (whose curly braces will be stripped out)
 */
bool FSMLDriver::Export(const std::string & c_code_block)
{
	bool ret_val = false;

	if (export_.length() == 0) {
		export_ = c_code_block;
		// strip starting and ending curly braces
		export_ = export_.substr(1, export_.size()-2);
		ret_val = true;
	}
	else {
		lastError_ = "'export' section already defined";
	}

	return ret_val;
}


/**
 * @brief   This method stores the C code contained in the time section
 * @param   c_code_block	string containing the C code block (whose curly braces will be stripped out)
 */
bool FSMLDriver::TimeSpec(const std::string & c_code_block)
{
	bool ret_val = false;

	if (timeSpec_.length() == 0) {
		if (periodSpec_.length() == 0) {
			timeSpec_ = c_code_block;
			// strip starting and ending curly braces
			timeSpec_ = timeSpec_.substr(1, timeSpec_.size()-2);
			ret_val = true;
		}
		else {
			lastError_ = "'period' section already defined, 'time' section cannot be defined any more";
		}
	}
	else {
		lastError_ = "'time' section already defined";
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

	if (periodSpec_.length() == 0) {
		if (timeSpec_.length() == 0) {
			periodSpec_ = c_code_block;
			// strip starting and ending curly braces
			periodSpec_ = periodSpec_.substr(1, periodSpec_.size()-2);
			ret_val = true;
		}
		else {
			lastError_ = "'time' section already defined, 'period' section cannot be defined any more";
		}
	}
	else {
		lastError_ = "'period' section already defined";
	}

	return ret_val;
}


bool FSMLDriver::AddVariable(const var_family_t f, const std::string & type, const std::string & name, const std::string & init_val)
{
	bool ret_val = false;

	// check if this variable is initialized
	if (init_val.size() > 0) {
		// check if this variable does not exist yet
		if (	(var_map_.find(name) == var_map_.end())
			&&	(timer_map_.find(name) == timer_map_.end()) ) 
		{
			// insert the new variable in its map
			var_map_[name] = new FSMVariable(f, type, name, init_val);
			ret_val = true;
		}
		else {
			lastError_ = "Redeclaration of variable " + name;
		}
	}
	else {
		lastError_ = "Uninitialized variable " + name;
	}

	return ret_val;
}


bool FSMLDriver::AddTimer(const std::string & name, const std::string & init_val)
{
	bool ret_val = false;

	// check if time or period sections have been defined
	if (timeSpec_.size() > 0 || periodSpec_.size() > 0) {

		// check if this timer does not exist yet
		if (	(var_map_.find(name) == var_map_.end())
			&&	(timer_map_.find(name) == timer_map_.end()) ) 
		{
			// insert the new timer in its map
			timer_map_[name] = new FSMTimer(name, init_val);
			ret_val = true;
		}
		else {
			lastError_ = "Redeclaration of variable " + name;
		}

	}
	else {
		lastError_ = "Timer declared without a time/period section";
	}

	return ret_val;
}


bool FSMLDriver::AddState(FSMState * s)
{
	bool ret_val = false;

	// check if the state name is unique
	if (s != nullptr && state_map_.find(s->Name()) == state_map_.end()) {
		state_map_[s->Name()] = s;
		ret_val = true;
	}

	lastError_ = "State <" + s->Name() + "> redefined";
	return ret_val;
}

FSMState * FSMLDriver::ResetState()
{
	for(auto s : state_map_) { 
		if(s.second->HasType(kStateTypeReset)) {
			return s.second;
		} 
	}
	return nullptr;
}

FSMState * FSMLDriver::ErrorState()
{
	for(auto s : state_map_) { 
		if(s.second->HasType(kStateTypeErr)) {
			return s.second;
		} 
	}
	return nullptr;
}

parse_result_t FSMLDriver::PopUntil()
{
	parse_result_t res = ParseResult_OK;

	/* TODO: create transitions due to this FSMUntil and destroy this FSMUntil after */ 
	FSMUntil * u = until_stack_.top();

	// add retry transition to all internal states
	std::vector<FSMState *> & untilStates = u->States();
	FSMState * firstS = untilStates[0];
	bool retry_actuator_exists = false;
	for (int i=0; i<untilStates.size(); ++i) {
		if (untilStates[i]->SetEndStateForRetryTrans(firstS) == true) {
			retry_actuator_exists = true;
		}
	}
	if (retry_actuator_exists == false) {
		lastError_ = "Until block has no retry actuators";
		res = ParseResult_WARN;
	}

	// add exit transition for the first state
	firstS->AddTransition(u->ExitTransition());

	// add first state to the until_first_states
	until_first_states_.push_back(firstS);

	// delete the current Until scope
	until_stack_.pop();	

	return res;
}


/**
 * @brief   This method builds the FSML Graph that contains states and transitions
 * \return	true if successfull, false if any error occurred (call GetLastError() to have a description of the error)
 */
bool FSMLDriver::BuildGraph()
{
	unsigned int error_codes_counter = 1;

	// check there is a reset state
	if (ResetState() == nullptr) {
		lastError_ = "Missing reset state";
		return false;
	}

	// check transitions are correct 
	for (auto & s : state_map_) {
		FSMState * curS = s.second;
		for (FSMTransition * t : curS->Transitions()) {
			// check condition
			if (t->CheckCondition() == false) {
				lastError_ = "Condition <" + t->Condition() + "> in state <" + curS->Name() + "> is invalid";
				return false;
			}
			// check destination
			if (t->CheckDestination() == false) {
				lastError_ = "Arrival state <" + t->EndState() + "> on transition " + t->Condition() + " in state <" + curS->Name() + "> is not reachable (may not exist)";
				return false;
			}
			// if correct ...
			else {
				// add eventual error code to the errors map
				std::string err_code = t->ErrorCode();
				if ((err_code.size() > 0) && (error_map_.find(err_code) == error_map_.end())) {
					error_map_[err_code] =  error_codes_counter++;
				}
			}
		}
	}

	return true;
}



/**
 * @brief   This method translates the FSML graph and creates a graphics representation of the FSM
 *          according to the DOT format defined here (https://graphviz.org/doc/info/lang.html)
 * @param   file_name	output file name for translation (if empty translates to the default fsm.dot)
 * \return	true if successfull, false if any error occurred
 */
bool FSMLDriver::TranslateToDOT(const std::string & file_name)
{
	bool ret_val = false;
	std::string out_file = file_name.size() > 0 ? file_name : kDefaultOutputDOTFile_;

	// open the output C file
	FILE * fp = fopen(out_file.c_str(), "w+");
	if (fp != nullptr) {

		// start graph
		fprintf(fp, "digraph %s {\n", fsmName_.c_str());
		
		// reset state
		fprintf(fp, "{node [style = \"invis\"] __fsmlReset}\n");
		fprintf(fp, "{node [style=\"bold\" shape=\"circle\"] %s}\n", ResetState()->Name().c_str());
		
		// error state
		if (ErrorState() != nullptr) {
			std::string shape = ErrorState()->HasType(kStateTypeEnd) ? "doublecircle" : "circle";
			fprintf(fp, "{node [color=\"black\" fillcolor=\"red\" style=\"filled\" shape=\"%s\"] %s}\n", shape.c_str(), ErrorState()->Name().c_str());
		}
		
		// final states
		fprintf(fp, "{node [shape=\"doublecircle\"] ");
		for(auto & s : state_map_) {
			if(s.second->HasType(kStateTypeEnd)) {
				fprintf(fp, "%s ", s.second->Name().c_str());
			}
		}
		fprintf(fp, "}\n");
		
		// other states and transitions
		fprintf(fp, "node [shape=\"circle\"]\n");
		fprintf(fp, "__fsmlReset -> %s [label=\"reset\"]\n", ResetState()->Name().c_str());
		for(auto & s : state_map_) {
			FSMState * curS = s.second;
			for(FSMTransition * t : curS->Transitions()) {
				fprintf(fp, "%s -> %s [label=\"%s\"]\n", curS->Name().c_str(), t->EndState().c_str(), t->ConditionStr().c_str());
			}
		}
		
		// end graph
		fprintf(fp, "}\n");
		
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
int FSMLDriver::Parse(const std::string& fileName)
{
	int res;

	filename_ = fileName;
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
void FSMLDriver::error(const std::string& msg)
{
	std::cerr << THIS_PARSER << msg << std::endl;
}


void FSMLDriver::error(FSML::location const & l, const std::string& msg)
{
	fprintf(stderr, "%s:%d: %s: %s\n", // "%s:%d:%d: %s: %s\n", (use this to add column number)
			l.begin.filename->c_str(),
			l.begin.line,
			// 		(to add column number look at the example in the lexer here 
			//  	https://opensource.apple.com/source/bison/bison-14/examples/calc++
			// 		but there is something more to add probably)
			// l.begin.column,	
			"error",
			msg.c_str()
	);
}

void FSMLDriver::warning(FSML::location const & l, const std::string& msg)
{
	fprintf(stderr, "%s:%d: %s: %s\n", // "%s:%d:%d: %s: %s\n", (use this to add column number)
			l.begin.filename->c_str(),
			l.begin.line,
			// 		(to add column number look at the example in the lexer here 
			//  	https://opensource.apple.com/source/bison/bison-14/examples/calc++
			// 		but there is something more to add probably)
			// l.begin.column,	
			"warning",
			msg.c_str()
	);
}
