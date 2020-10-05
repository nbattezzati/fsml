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

std::string tmp_initializer;
std::string tmp_ptr_type;
std::string tmp_declarator;
%}

%parse-param {FSMLDriver& driver}
%lex-param {FSMLDriver& driver}

%{
#include "FSMLDriver.h"
#include "fsml_inner.h"
%}

%union {
	int i;
	float f;
	std::string *s;
	var_family_t vf;
}


%start fsml

%token END_OF_FILE 0



%token DECL_KEY TIME_KEY PERIOD_KEY FSM_KEY LCB RCB VAR_KEY INPUT_KEY OUTPUT_KEY TIMER_KEY STATE_KEY ON TIMEOUT_KEY GO ERR RETRY START VOID CHAR SHORT INT LONG FLOAT DOUBLE SIGNED UNSIGNED UNION STRUCT ENUM STAR COMMA END LSB RSB OUT UNTIL_KEY SC EQUAL LB RB ERROR
%token <s> C_CODE_BLOCK C_CONDITION_BLOCK IDENTIFIER CHARACTER_CONSTANT
%token <i> INTEGER_CONSTANT
%token <f> FLOATING_CONSTANT



%%


fsml	: init_section_list fsm

init_section_list : init_section
				  | init_section_list init_section
				  | /* empty */
				  ;

init_section : declaration
			 | time
			 ;

declaration : DECL_KEY C_CODE_BLOCK { driver.Decl(*($<s>2)); } ;

time : time_specifier 
	 | period_specifier
	 ;

time_specifier : TIME_KEY C_CODE_BLOCK { 
		if (driver.TimeSpec(*($<s>2)) == false) { 
			driver.error(@$, driver.GetLastError()); 
			YYERROR; 
		}; 
	} ;

period_specifier : PERIOD_KEY C_CODE_BLOCK {
		if (driver.PeriodSpec(*($<s>2)) == false) { 
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
													$<vf>1, 
													*($<s>2) + std::string(" ") + tmp_ptr_type, 
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

type_specifier_list : type_specifier						{ $<s>$ = $<s>1; }
					| type_specifier_list type_specifier 	{ $<s>$->append(" " + *($<s>2)); }
					;

variable_specifier : VAR_KEY		{ $<vf>$ = VariableFamily_VAR; }
				   | INPUT_KEY		{ $<vf>$ = VariableFamily_INPUT; }
				   | OUTPUT_KEY		{ $<vf>$ = VariableFamily_OUTPUT; }
				   ;

type_specifier : VOID				{ $<s>$ = new std::string("void"); }
			   | CHAR				{ $<s>$ = new std::string("char"); }
			   | SHORT				{ $<s>$ = new std::string("short"); }
			   | INT				{ $<s>$ = new std::string("int"); }
			   | LONG				{ $<s>$ = new std::string("long"); }
			   | FLOAT				{ $<s>$ = new std::string("float"); }
			   | DOUBLE				{ $<s>$ = new std::string("double"); }
			   | SIGNED				{ $<s>$ = new std::string("signed"); }
			   | UNSIGNED			{ $<s>$ = new std::string("unsigned"); }
			   | struct_or_union_specifier	{ $<s>$ = $<s>1; }
			   | enum_specifier		{ $<s>$ = $<s>1; }
			   | typedef_name		{ $<s>$ = $<s>1; }
			   ;

struct_or_union_specifier : struct_or_union IDENTIFIER ;

struct_or_union : STRUCT			{ $<s>$ = new std::string("struct"); }
				| UNION				{ $<s>$ = new std::string("union"); }
				;

enum_specifier : ENUM IDENTIFIER	{ $<s>$ = new std::string("enum" + *($<s>1)); } 
			   ;

typedef_name : IDENTIFIER			{ $<s>$ = $<s>1; } 
			 ;

init_declarator : declarator EQUAL initializer ;

initializer : constant			{ tmp_initializer = *($<s>1); }
			| LCB constant RCB	{ tmp_initializer = std::string("{" + *($<s>2) + "}"); }
			;

declarator : pointer direct_declarator	{ /*tmp_declarator = *$<s>2;*/ }
		   | direct_declarator			{ /*tmp_declarator = *$<s>1;*/ }
		   ;

direct_declarator : IDENTIFIER 			{ tmp_declarator = *$<s>1; }
				  ;

pointer : STAR							{ tmp_ptr_type.append("*"); }
		| STAR pointer					{ tmp_ptr_type.append("*"); }
		;

constant : INTEGER_CONSTANT				{ $<s>$ = new std::string(std::to_string($<i>1)); }
		 | CHARACTER_CONSTANT			{ $<s>$ = $<s>1; }
		 | FLOATING_CONSTANT			{ $<s>$ = new std::string(std::to_string($<f>1)); }
		 | enumeration_constant			{ $<s>$ = $<s>1; }
		 ;

enumeration_constant : IDENTIFIER 		{ $<s>$ = $<s>1; }
					 ;

timer_specifier : TIMER_KEY IDENTIFIER LB timer_initializer RB 
					{
						if (driver.AddTimer(*($<s>2), *($<s>4)) == false) {
							driver.error(@$, driver.GetLastError()); 
							YYERROR; 
						};
					}
				;

timer_initializer : INTEGER_CONSTANT 	{ $<s>$ = new std::string(std::to_string($<i>1)); }
				  | IDENTIFIER			{ $<s>$ = $<s>1; }
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
