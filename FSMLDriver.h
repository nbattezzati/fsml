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
#include <stack>
#include <map>

namespace FSML{
	class location;
	class FSMLParser;
}


class FSMLDriver;


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

	inline var_family_t Family() const { return family_; }
	inline std::string Type() const { return type_; }
	inline std::string Name() const { return name_; }
	inline std::string InitVal() const { return init_val_; }

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

	inline std::string Name() const { return name_; }
	inline std::string InitVal() const { return init_val_; }

private:
	std::string name_;
	std::string init_val_;
};


typedef enum {
	TransActuator_GO,
	TransActuator_ERR,
	TransActuator_RETRY,
} trans_actuator_t;

class FSMTransition
{
public:
	FSMTransition(FSMLDriver & driver, const std::string & condition)
		: driver_(driver), condition_(condition) {}
	virtual ~FSMTransition() {}

	inline void Code(const std::string & code) { code_ = code; }
	inline std::string Code() const { return code_; }
	inline std::string Condition() const { return condition_; }
	inline void Actuator(const trans_actuator_t act) { actuator_ = act; }
	inline trans_actuator_t Actuator() const { return actuator_; }
	inline void Timer(const std::string & timer) { timer_ = timer; }
	inline std::string Timer() const { return timer_; }
	inline void EndState(const std::string & endState) { endState_ = endState; }
	inline std::string EndState() const { return endState_; }
	inline void ErrorCode(const std::string & errorCode) { errorCode_ = errorCode; }
	inline std::string ErrorCode() const { return errorCode_; }

	inline virtual std::string ConditionStr() const { return condition_; }

	virtual bool CheckCondition();
	bool CheckDestination();

protected:
	std::string condition_;
	std::string code_;
	trans_actuator_t actuator_;
	std::string timer_;
	std::string endState_;
	std::string errorCode_;
	FSMLDriver & driver_;
};

class FSMTimeoutTransition : public FSMTransition
{
public:
	FSMTimeoutTransition(FSMLDriver & driver, const std::string & timeout) : FSMTransition(driver, timeout) {}
	virtual ~FSMTimeoutTransition() {}

	inline std::string ConditionStr() const override { return condition_ + ".expired()"; }

	bool CheckCondition() override;
};

class FSMUntilTransition : public FSMTransition
{
public:
	FSMUntilTransition(FSMLDriver & driver, const std::string & until) : FSMTransition(driver, until) {}
	virtual ~FSMUntilTransition() {}

	inline std::string ConditionStr() const override { return "retries < " + condition_; }

	bool CheckCondition() override;
};


typedef enum {
	kStateTypeStart,
	kStateTypeEnd,
	kStateTypeErr,
} state_type_t;

class FSMState
{
public:
	FSMState(FSMLDriver & driver) : driver_(driver) {}
	~FSMState() {}

	inline void Name(const std::string & name) { name_ = name; }
	inline std::string Name() const { return name_; }
	inline void AddType(state_type_t type) { types_.push_back(type); }
	inline void Code(const std::string & code) { code_ = code; }
	inline std::string Code() const { return code_; } 
	inline void AddTransition(FSMTransition * t) { transitions_.push_back(t); }
	inline std::vector<FSMTransition *> & Transitions() { return transitions_; }

	bool HasType(state_type_t type);
	bool AddOutput(const std::string & output, const std::string & out_code);
	void SetEndStateForRetryTrans(FSMState * s);

	inline std::string ToString() { return std::string(
		"S<" + name_ + ">" + 
		" [" + TypesToString_() + "]" +
		" {" + code_ + "}"); 
	}

private:
	inline std::string TypesToString_()
	{
		std::string tmp;
		if (types_.size() > 0) {
			for (int t = 0; t < types_.size()-1; ++t) {
				tmp += std::to_string(types_[t]) + ",";
			}
			tmp.append(std::to_string(types_[types_.size()-1]));
		}
		return tmp;
	}

	std::string name_;
	std::vector<state_type_t> types_;
	std::string code_;
	std::vector<FSMTransition *> transitions_;
	std::map<std::string, std::string> output_map_;
	
	FSMLDriver & driver_;
};


class FSMUntil
{
public:
	FSMUntil() {}
	~FSMUntil() {}

	inline void AddState(FSMState * s) { states_.push_back(s); }
	inline std::vector<FSMState *> & States() { return states_; }
	inline void ExitTransition(FSMUntilTransition * t) { exitTransition_ = t; }
	inline FSMUntilTransition * ExitTransition() { return exitTransition_; }

private:
	std::vector<FSMState *> states_;
	FSMUntilTransition * exitTransition_ = nullptr;
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


	inline void FsmName(const std::string & name) { fsmName_ = name; }
	inline std::string & FsmName() { return fsmName_; }
	void Decl(const std::string & c_code_block);
	bool TimeSpec(const std::string & c_code_block);
	bool PeriodSpec(const std::string & c_code_block);
	bool AddVariable(const var_family_t f, const std::string & type, const std::string & name, const std::string & init_val);
	inline bool varExists(const std::string & v) { return var_map_.find(v) != var_map_.end(); }
	inline bool TimerExists(const std::string & t) { return timer_map_.find(t) != timer_map_.end(); }
	bool AddTimer(const std::string & name, const std::string & init_val);
	bool AddState(FSMState * s);
	FSMState * ErrorState();
	inline bool StateExists(const std::string & s) { return state_map_.find(s) != state_map_.end(); }

	inline void PushUntil(FSMUntil * u) { until_stack_.push(u); }
	void PopUntil();
	inline FSMUntil * CurUntil() { return until_stack_.top(); }

	bool BuildGraph();

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
	static void error(FSML::location const & l, const std::string& m);
	static void error(const std::string& errorMsg);
	inline void SetlastError(const std::string & err) { lastError_ = err; }
	inline std::string GetLastError() const { return lastError_; }

	//---------------------------------------------------/
	
private:
	std::string fsmName_;

	// code contained in the declaration section (if any)
	std::string decl_;

	// code contained in the time secction (if any)
	std::string timeSpec_;

	// code contained in the period section (if any)
	std::string periodSpec_;

	std::string lastError_;

	std::map<std::string, FSMVariable *> var_map_;
	std::map<std::string, FSMTimer *> timer_map_;
	std::map<std::string, FSMState *> state_map_;

	std::stack<FSMUntil *> until_stack_;

	const std::string kDefaultOutputCFile_ = "fsm.c";
};

	
#endif //FSML_DRIVER_H_
