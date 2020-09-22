%skeleton "lalr1.cc"
%defines
%define "parser_class_name" "FSMLParser"

%locations

%{
#include <stdio.h>
#include <string>
#include "fsml.h"

//#define DEBUG

class FSMLDriver;
%}


%parse-param {FSMLDriver& driver}
%lex-param {FSMLDriver& driver}

%union {
	int num;
	std::string *s;
	bool b;
}


%{
#include "FSMLDriver.h"
#include "fsml.h"
%}

%start actelPdc

%token END_OF_FILE 0
%token YES NO SET_LOCATION SET_PRESERVE FIXED




%token <num> INTEGER
%token <s> IO_BANK_COMMAND
%token <s> LOCAL_CLOCK_COMMAND
%token <s> REGION_COMMAND
%token <s> IO_COMMAND
%token <s> HIERARCHICAL_IDENTIFIER

%type <num> x_loc
%type <num> y_loc
%type <b> fixed_val
%type <s> hier_name


%%
						
actelPdc		:	io_bank_settings local_clock_constraints region_constraints io_constraints core_cell_constraints
					{
						#ifdef DEBUG
						printf("actelPdc file successfully recognized\n");
						#endif
					}
				;

io_bank_settings	:	io_bank_settings_list 
						{
							#ifdef DEBUG
							printf("I/O Banks Settings successfully recognized\n");
							#endif
						}
					|	/* empty */
					;

io_bank_settings_list	:	io_bank_settings_list io_bank_setting
						|	io_bank_setting
						;

io_bank_setting	:	IO_BANK_COMMAND
					;

local_clock_constraints	:	local_clock_constraints_list 
							{
								#ifdef DEBUG
								printf("Local Clock Constraints successfully recognized\n");
								#endif
							}
						|	/* empty */
						;

local_clock_constraints_list	:	local_clock_constraints_list local_clock_constraint
								|	local_clock_constraint
								;

local_clock_constraint	:	LOCAL_CLOCK_COMMAND
						;

region_constraints	:	region_constraints_list 
						{
							#ifdef DEBUG
							printf("Region Constraints successfully recognized\n");
							#endif
						}
					|	/* empty */
					;

region_constraints_list	:	region_constraints_list region_constraint
						|	region_constraint
						;

region_constraint	:	REGION_COMMAND
					;

io_constraints	:	io_constraints_list 
					{
						#ifdef DEBUG
						printf("I/O Constraints successfully recognized\n");
						#endif
					}
				|	/* empty */
				;

io_constraints_list	:	io_constraints_list io_constraint
					|	io_constraint
					;

io_constraint	:	IO_COMMAND
				;

core_cell_constraints	:	core_cell_constraints_list 
							{
								#ifdef DEBUG
								printf("Core Cell Constraints successfully recognized\n");
								#endif
							}
						|	/* empty */
						;

core_cell_constraints_list	:	core_cell_constraints_list core_cell_constraint
							|	core_cell_constraint
							;

core_cell_constraint	:	set_preserve_comm
						|	set_location_comm
						;

set_preserve_comm		:	SET_PRESERVE hier_name
							{
								//printf("<set_preserve %s> command found\n", ($<s>2)->c_str());
								//printf("purged string: <%s>\n", StringRemoveEscapes(*($<s>2)).c_str());
								//printf("looking for instance ...\n");
								//fflush(stdout);
								/*
								EdifInstance * i;
								if((i = driver.getInstanceByPath(StringRemoveEscapes(*($<s>2)))) == NULL){
									return 1;
								}
								i->getActelConstr()->setPreserve(true);
								*/
								//printf("%s\n", i->getInfo().c_str());
							}
						;

set_location_comm		:	SET_LOCATION hier_name FIXED fixed_val x_loc y_loc
							{
								//printf("<set_location %s %d %d> command found\n", ($<s>2)->c_str(), $<num>5, $<num>6);
								//printf("purged string: <%s>\n", StringRemoveEscapes(*($<s>2)).c_str());
								//printf("looking for instance ...\n");
								//fflush(stdout);
								//if(driver.getInstanceByPath(StringRemoveEscapes(*($<s>2))) != NULL){
								//	printf("done\n");
								//}
								//else{
								//	printf("erroreeee!!!\n"); fflush(stdout);
								//}
								/*
								EdifInstance * i;
								if((i = driver.getInstanceByPath(StringRemoveEscapes(*($<s>2)))) == NULL){
									return 1;
								}
								i->getActelConstr()->setFixed($<b>4);
								i->getActelConstr()->setLocX($<num>5);
								i->getActelConstr()->setLocY($<num>6);
								*/
								//printf("%s\n", i->getInfo().c_str());
							}
						;

hier_name				:	HIERARCHICAL_IDENTIFIER
						;

fixed_val				:	YES	{$<b>$ = true;}
						|	NO {$<b>$ = false;}
						;

x_loc					:	INTEGER
						;

y_loc					:	INTEGER
						;



%%

void FSML::FSMLParser::error(const FSML::FSMLParser::location_type& l, const std::string& m)
{
	driver.error(l, m);
}
