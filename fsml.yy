%skeleton "lalr1.cc"
%defines
%define api.parser.class {FSMLParser}
%define api.value.type variant
%define api.value.automove

%locations


%{
#include <iostream>
#include <stdio.h>
#include <string>
#include "fsml.h"


#ifdef DEBUG
#define log(...) printf(__VA_ARGS__)
#else
#define log(...)
#endif

class FSMLDriver;

std::string tmp_initializer;
std::string tmp_ptr_type;
std::string tmp_declarator;
%}

%parse-param {FSMLDriver& driver}
%lex-param {FSMLDriver& driver}

%{
#include "FSMLDriver.h"
#include "fsml_inner.h"

FSMState * tmpState = nullptr;
FSMTransition * tmpTrans = nullptr;
%}



%start fsml

%token END_OF_FILE 0



%token DECL_KEY TIME_KEY PERIOD_KEY FSM_KEY LCB RCB VAR_KEY INPUT_KEY OUTPUT_KEY TIMER_KEY STATE_KEY ON TIMEOUT_KEY GO ERR RETRY START VOID CHAR SHORT INT LONG FLOAT DOUBLE SIGNED UNSIGNED UNION STRUCT ENUM STAR COMMA END LSB RSB OUT UNTIL_KEY SC EQUAL LB RB ERROR
%token <std::string> C_CODE_BLOCK C_CONDITION_BLOCK IDENTIFIER CHARACTER_CONSTANT
%token <int> INTEGER_CONSTANT
%token <float> FLOATING_CONSTANT

%type <std::string> type_specifier_list type_specifier struct_or_union_specifier struct_or_union enum_specifier typedef_name state_specifier
%type <std::string> constant enumeration_constant timer_initializer state_c_code until_condition

%type <var_family_t> variable_specifier

%type <state_type_t> state_type



%%


fsml	: init_section_list fsm

init_section_list : init_section
				  | init_section_list init_section
				  | /* empty */
				  ;

init_section : declaration
			 | time
			 ;

declaration : DECL_KEY C_CODE_BLOCK { driver.Decl($2); } ;

time : time_specifier 
	 | period_specifier
	 ;

time_specifier : TIME_KEY C_CODE_BLOCK { 
		if (driver.TimeSpec($2) == false) { 
			driver.error(@$, driver.GetLastError()); 
			YYERROR; 
		}; 
	} ;

period_specifier : PERIOD_KEY C_CODE_BLOCK {
		if (driver.PeriodSpec($2) == false) { 
			driver.error(@$, driver.GetLastError()); 
			YYERROR; 
		}; 
	} ;

fsm : FSM_KEY IDENTIFIER LCB fsm_objects_list RCB ;

fsm_objects_list : fsm_object
				 | fsm_objects_list fsm_object
				 ;

fsm_object : variable_declaration 
		   | state
		   | until_retry
		   ;

variable_declaration : variable_specifier type_specifier_list init_declarator SC
						{
							bool result = driver.AddVariable(
													$1, 
													$2 + std::string(" ") + tmp_ptr_type, 
													tmp_declarator, 
													tmp_initializer);
							tmp_initializer.clear();
							tmp_ptr_type.clear();
							if (result == false) {
								driver.error(@$, driver.GetLastError()); 
								YYERROR; 
							}
						}
					 | timer_specifier SC 
					 ;

type_specifier_list : type_specifier						{ $$ = $1; }
					| type_specifier_list type_specifier 	{ $$.append(" " + $2); }
					;

variable_specifier : VAR_KEY		{ $$ = VariableFamily_VAR; }
				   | INPUT_KEY		{ $$ = VariableFamily_INPUT; }
				   | OUTPUT_KEY		{ $$ = VariableFamily_OUTPUT; }
				   ;

type_specifier : VOID				{ $$ = std::string("void"); }
			   | CHAR				{ $$ = std::string("char"); }
			   | SHORT				{ $$ = std::string("short"); }
			   | INT				{ $$ = std::string("int"); }
			   | LONG				{ $$ = std::string("long"); }
			   | FLOAT				{ $$ = std::string("float"); }
			   | DOUBLE				{ $$ = std::string("double"); }
			   | SIGNED				{ $$ = std::string("signed"); }
			   | UNSIGNED			{ $$ = std::string("unsigned"); }
			   | struct_or_union_specifier	{ $$ = $1; }
			   | enum_specifier		{ $$ = $1; }
			   | typedef_name		{ $$ = $1; }
			   ;

struct_or_union_specifier : struct_or_union IDENTIFIER { $$ = $1 + $2; };

struct_or_union : STRUCT			{ $$ = std::string("struct"); }
				| UNION				{ $$ = std::string("union"); }
				;

enum_specifier : ENUM IDENTIFIER	{ $$ = std::string("enum" + $2); } 
			   ;

typedef_name : IDENTIFIER			{ $$ = $1; } 
			 ;

init_declarator : declarator EQUAL initializer ;

initializer : constant			{ tmp_initializer = $1; }
			| LCB constant RCB	{ tmp_initializer = std::string("{" + $2 + "}"); }
			;

declarator : pointer direct_declarator
		   | direct_declarator
		   ;

direct_declarator : IDENTIFIER 			{ tmp_declarator = $1; }
				  ;

pointer : STAR							{ tmp_ptr_type.append("*"); }
		| STAR pointer					{ tmp_ptr_type.append("*"); }
		;

constant : INTEGER_CONSTANT				{ $$ = std::to_string($1); }
		 | CHARACTER_CONSTANT			{ $$ = $1; }
		 | FLOATING_CONSTANT			{ $$ = std::to_string($1); }
		 | enumeration_constant			{ $$ = $1; }
		 ;

enumeration_constant : IDENTIFIER 		{ $$ = $1; }
					 ;

timer_specifier : TIMER_KEY IDENTIFIER LB timer_initializer RB 
					{
						if (driver.AddTimer($2, $4) == false) {
							driver.error(@$, driver.GetLastError()); 
							YYERROR; 
						};
					}
				;

timer_initializer : INTEGER_CONSTANT 	{ $$ = std::to_string($1); }
				  | IDENTIFIER			{ $$ = $1; }
				  ;

state : state_specifier state_decorator_list SC { };

state_specifier : STATE_KEY { tmpState = new FSMState(driver); } 
				  state_type_specifier 
				  IDENTIFIER { tmpState->Name($4); } 
				  state_c_code { tmpState->Code($6); } 
				;

state_type_specifier : LSB state_type_list RSB
					 | /* empty */
					 ;

state_c_code : C_CODE_BLOCK		{ $$ = $1; }
			 | /* empty */		{ $$ = std::string(); }
			 ;

state_type_list : state_type 							{ tmpState->AddType($1); }
				| state_type_list COMMA state_type		{ tmpState->AddType($3); }
				;

state_type : START		{ $$ = kStateTypeStart; }
		   | END		{ $$ = kStateTypeEnd; }
		   | ERR		{ $$ = kStateTypeErr; }
		   ;

state_decorator_list : state_decorator
					 | state_decorator_list state_decorator
					 | /* empty */
					 ;


state_decorator : transition_specifier
				| output_specifier
				;


transition_specifier : ON transition_condition transition_c_code transition_actuator timer_actuator ;

transition_c_code : C_CODE_BLOCK	{ tmpTrans->Code($1); }
				  | /* empty */
				  ;

transition_condition : C_CONDITION_BLOCK				{ tmpTrans = new FSMTransition($1); }
					 | TIMEOUT_KEY LB IDENTIFIER RB		{ tmpTrans = new FSMTimeoutTransition($3); }
					 ;

transition_actuator : GO IDENTIFIER		{ tmpTrans->Actuator(TransActuator_GO); tmpTrans->EndState($2); }
					| ERR IDENTIFIER	{ tmpTrans->Actuator(TransActuator_ERR); tmpTrans->ErrorCode($2); }
					| RETRY				{ tmpTrans->Actuator(TransActuator_RETRY); }
					;

timer_actuator : START IDENTIFIER 	{ tmpTrans->Timer($2); }
			   | /* empty*/
			   ;

output_specifier : OUT IDENTIFIER EQUAL C_CODE_BLOCK { 
						if (tmpState->AddOutput($2, $4) == false) {
							driver.error(@$, driver.GetLastError()); 
							YYERROR;
						} 
				 } ;

until_retry : UNTIL_KEY until_condition { driver.PushUntil(new FSMUntil($2)); } 
			  LCB until_object_list RCB transition_actuator SC;

until_condition : LB INTEGER_CONSTANT RB		{ $$ = std::to_string($2); }
				| LB enumeration_constant RB	{ $$ = $2; }
				;

until_object_list : until_object
				  | until_object_list until_object
				  ;

until_object : state { driver.CurUntil()->AddState(tmpState); }
			 | until_retry
			 ;



%%

void FSML::FSMLParser::error(const FSML::FSMLParser::location_type& l, const std::string& m)
{
	driver.error(l, m);
}
