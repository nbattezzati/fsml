%skeleton "lalr1.cc"
%defines
%define api.parser.class {FSMLParser}

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
%}


%parse-param {FSMLDriver& driver}
%lex-param {FSMLDriver& driver}

%union {
	int i;
	float f;
	std::string *s;
}


%{
#include "FSMLDriver.h"
#include "fsml_inner.h"
%}

%start fsml

%token END_OF_FILE 0



%token DECL_KEY TIME_KEY PERIOD_KEY FSM_KEY LCB RCB VAR_KEY INPUT_KEY OUTPUT_KEY TIMER_KEY STATE_KEY ON TIMEOUT_KEY GO ERR RETRY START VOID CHAR SHORT INT LONG FLOAT DOUBLE SIGNED UNSIGNED UNION STRUCT ENUM STAR COMMA END LSB RSB OUT UNTIL_KEY SC EQUAL LB RB
%token <s> C_CODE_BLOCK C_CONDITION_BLOCK IDENTIFIER CHARACTER_CONSTANT ENUMERATION_CONSTANT
%token <i> INTEGER_CONSTANT
%token <f> FLOATING_CONSTANT


%%


fsml	: declaration time fsm { std::cout << "\n\n PARSING COMPLETE! \n\n"; };

declaration : DECL_KEY C_CODE_BLOCK 
			| /* empty */ 
			;

time : time_specifier 
	 | period_specifier
	 | /* empty */
	 ;

time_specifier : TIME_KEY C_CODE_BLOCK ;

period_specifier : PERIOD_KEY C_CODE_BLOCK ;

fsm : FSM_KEY IDENTIFIER LCB fsm_objects_list RCB ;

fsm_objects_list : fsm_object
				 | fsm_objects_list fsm_object
				 ;

fsm_object : variable_declaration 
		   | state
		   | until_retry
		   ;

variable_declaration : variable_specifier type_specifier_list init_declarator SC
					 | timer_specifier SC ;

type_specifier_list : type_specifier
					| type_specifier_list type_specifier
					;

variable_specifier : VAR_KEY
				   | INPUT_KEY
				   | OUTPUT_KEY
				   ;

type_specifier : VOID
			   | CHAR
			   | SHORT
			   | INT
			   | LONG
			   | FLOAT
			   | DOUBLE
			   | SIGNED
			   | UNSIGNED
			   | struct_or_union_specifier
			   | enum_specifier
			   | typedef_name
			   ;

struct_or_union_specifier : struct_or_union IDENTIFIER ;

struct_or_union : STRUCT
				| UNION
				;

enum_specifier : ENUM IDENTIFIER ;

typedef_name : IDENTIFIER ;

init_declarator : declarator EQUAL constant ;

declarator : pointer direct_declarator
		   | direct_declarator
		   ;

direct_declarator : IDENTIFIER ;

pointer : STAR
		| STAR pointer
		;

constant : INTEGER_CONSTANT
		 | CHARACTER_CONSTANT
		 | FLOATING_CONSTANT
		 | enumeration_constant
		 ;

enumeration_constant : IDENTIFIER ;

timer_specifier : TIMER_KEY IDENTIFIER LB timer_initializer RB ;

timer_initializer : INTEGER_CONSTANT 
				  | IDENTIFIER
				  ;

state : state_specifier state_decorator_list SC ;

state_specifier : STATE_KEY state_type_specifier IDENTIFIER state_c_code ;

state_type_specifier : LSB state_type_list RSB
					 | /* empty */
					 ;

state_c_code : C_CODE_BLOCK
			 | /* empty */
			 ;

state_type_list : state_type
				| state_type_list COMMA state_type
				;

state_type : START
		   | END
		   | ERR
		   ;

state_decorator_list : state_decorator
					 | state_decorator_list state_decorator
					 | /* empty */
					 ;


state_decorator : transition_specifier
				| output_specifier
				;


transition_specifier : ON transition_condition transition_c_code transition_actuator timer_actuator ;

transition_c_code : C_CODE_BLOCK
				  | /* empty */
				  ;

transition_condition : C_CONDITION_BLOCK
					 | TIMEOUT_KEY LB IDENTIFIER RB
					 ;

transition_actuator : GO IDENTIFIER
					| ERR IDENTIFIER
					| RETRY
					;

timer_actuator : START IDENTIFIER 
			   | /* empty*/
			   ;

output_specifier : OUT IDENTIFIER EQUAL C_CODE_BLOCK ;

until_retry : UNTIL_KEY until_condition LCB until_object_list RCB transition_actuator  SC;

until_condition : LB INTEGER_CONSTANT RB
				| LB enumeration_constant RB
				;

until_object_list : until_object
				  | until_object_list until_object
				  ;

until_object : state 
			 | until_retry
			 ;



%%

void FSML::FSMLParser::error(const FSML::FSMLParser::location_type& l, const std::string& m)
{
	driver.error(l, m);
}
