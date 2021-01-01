/**
 *       @file  fsml.lexpp
 *      @brief  The scanner definition for the FSML (Finite State Machine Language)
 *
 *
 *     @author  Niccolo` Battezzati, niccolo.battezzati@argotecgroup.com
 *
 *   @internal
 *     Created  20/09/2020
 *     Company  Argotec S.r.l
 *   Copyright  Copyright (c) 2020, Argotec S.r.l
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



%{
#include <stdio.h>
#include <string>
#include <errno.h>


#include "FSMLDriver.h"
#include "fsml.hh" 
#include "fsml_inner.h"

#ifdef DEBUG
#define log(...) printf(__VA_ARGS__)
#else
#define log(...)
#endif

#define yyterminate()	return token::END_OF_FILE

#define FSMLlval 		yylval 


typedef FSML::FSMLParser::token token;


int line = 1;			/* line counter */
int cb_cnt = 0;			/* counter for curly braces */
int b_cnt = 0;			/* counter for round brackets */

std::string tmp_str;	/* used to collect characters scanned by different rules in a unique token */

%}

%option noyywrap nounput batch stack

%s DECL TIME PERIOD FSM VAR TIMER STATE STATE_TYPE TIMEOUT UNTIL 
%x C_CODE C_CONDITION C_COMMENT FSML_COMMENT



GEN_IDENTIFIER	[a-zA-Z]([a-zA-Z0-9_]*)
INTEGER			[0-9]+
CHARACTER		\'.\'
FLOAT			[0-9]+(\.[0-9]+)*

%%


"decl"		{
				log("found: DECL\n");
				yy_push_state(DECL);
				return token::DECL_KEY;
			}

"time"	{
				log("found: TIME\n");
				yy_push_state(TIME);
				return token::TIME_KEY;
			}

"period"	{
				log("found: PERIOD\n");
				yy_push_state(PERIOD);
				return token::PERIOD_KEY;
			}

<DECL,TIME,PERIOD>"{"	{
				log("Beginning C-CODE\n");
				tmp_str += std::string(yytext);
				yy_push_state(C_CODE);
			}

<C_CODE>"{"	{
				tmp_str += std::string(yytext);
				cb_cnt++;
			}

<C_CODE>"}"	{
				tmp_str += std::string(yytext);
				cb_cnt--;
				if (cb_cnt < 0) {
					log("found: C_CODE\n");
					cb_cnt = 0;
					switch (yy_top_state()) {
						case DECL:
						case TIME:
						case PERIOD:
							yy_pop_state();
						break;

						default: break;
					}
					yy_pop_state();
					FSMLlval->emplace<std::string>(tmp_str); 
					tmp_str.clear();
					return token::C_CODE_BLOCK;
				}
			}

"fsm"		{
				log("found: FSM\n");
				yy_push_state(FSM);
				return token::FSM_KEY;
			}
			
<FSM>"{"	{
				log("found: LCB\n");
				return token::LCB;
			}


<FSM>"}"	{
				log("found: RCB\n");
				yy_pop_state();
				return token::RCB;
			}

"var"	{
				log("found: VAR\n");
				yy_push_state(VAR);
				return token::VAR_KEY;
			}

"input"	{
				log("found: INPUT\n");
				yy_push_state(VAR);
				return token::INPUT_KEY;
			}

"output"	{
				log("found: OUTPUT\n");
				yy_push_state(VAR);
				return token::OUTPUT_KEY;
			}

"timer"	{
				log("found: TIMER\n");
				yy_push_state(TIMER);
				return token::TIMER_KEY;
			}

<VAR,TIMER>";"	{
				log("found: SC\n");
				yy_pop_state();
				return token::SC;
			}

"void" {
				log("found: VOID\n");
				return token::VOID;
			}

"char" {
				log("found: CHAR\n");
				return token::CHAR;
			}

"short" {
				log("found: SHORT\n");
				return token::SHORT;
			}

"int" {
				log("found: INT\n");
				return token::INT;
			}

"long" {
				log("found: LONG\n");
				return token::LONG;
			}

"float" {
				log("found: FLOAT\n");
				return token::FLOAT;
			}

"double" {
				log("found: DOUBLE\n");
				return token::DOUBLE;
			}

"signed" {
				log("found: SIGNED\n");
				return token::SIGNED;
			}

"unsigned" {
				log("found: UNSIGNED\n");
				return token::UNSIGNED;
			}

"union" {
				log("found: UNION\n");
				return token::UNION;
			}

"struct" {
				log("found: STRUCT\n");
				return token::STRUCT;
			}

"enum" {
				log("found: ENUM\n");
				return token::ENUM;
			}

<VAR,TIMER,UNTIL>{INTEGER} {
				log("found: INTEGER %s\n", yytext);
				FSMLlval->emplace<int>(atoi(yytext));
				return token::INTEGER_CONSTANT;
			}

<VAR>{CHARACTER} {
				log("found: CHARACTER %s\n", yytext);
				FSMLlval->emplace<std::string>(yytext);
				return token::CHARACTER_CONSTANT;
			}

<VAR>{FLOAT} {
				log("found: FLOAT %s\n", yytext);
				FSMLlval->emplace<float>(atof(yytext));
				return token::FLOATING_CONSTANT;
			}

"until"	{
				log("found: UNTIL\n");
				yy_push_state(UNTIL);
				return token::UNTIL_KEY;
			}



"state"		{
				log("found: STATE\n");
				yy_push_state(STATE);
				return token::STATE_KEY;
			}

<STATE>"["	{
				log("found: LSB\n");
				yy_push_state(STATE_TYPE);
				return token::LSB;
			}

"reset" {
				log("found: RESET\n");
				return token::RESET;
			}

"end" {
				log("found: END\n");
				return token::END;
			}

"err" {
				log("found: ERR\n");
				return token::ERR;
			}

<STATE_TYPE>"]"	{
				log("found: RSB\n");
				yy_pop_state();
				return token::RSB;
			}

<STATE>"{"	{
				log("Beginning C_CODE\n");
				tmp_str += std::string(yytext);
				yy_push_state(C_CODE);
			}

"on"	{
				log("found: ON\n");
				return token::ON;
			}

<STATE>"("	{
				log("Beginning C_CONDITION\n");
				tmp_str += std::string(yytext);
				yy_push_state(C_CONDITION);
			}

<C_CONDITION>"("	{
				tmp_str += std::string(yytext);
				b_cnt++;
			}

<C_CONDITION>")"	{
				tmp_str += std::string(yytext);
				b_cnt--;
				if (b_cnt < 0) {
					log("found: C_CONDITION\n");
					b_cnt = 0;
					yy_pop_state();
					FSMLlval->emplace<std::string>(tmp_str); 
					tmp_str.clear();
					return token::C_CONDITION_BLOCK;
				}
			}

"timeout"	{
				log("found: TIMEOUT\n");
				yy_push_state(TIMEOUT);
				return token::TIMEOUT_KEY;
			}

<TIMEOUT>")"	{
				log("found RB\n");
				yy_pop_state();
				return token::RB;
			}

"go"	{
				log("found: GO\n");
				return token::GO;
			}

"retry"	{
				log("found: RETRY\n");
				return token::RETRY;
			}

"out"	{
				log("found: OUT\n");
				return token::OUT;
			}

"start" {
				log("found: START\n");
				return token::START;
			}

<UNTIL,STATE>";"	{
				log("found: SC\n");
				yy_pop_state();
				return token::SC;
			}

{GEN_IDENTIFIER} { 
				log("found: IDENTIFIER %s\n", yytext);
				FSMLlval->emplace<std::string>(yytext);
				return token::IDENTIFIER;
			}

"{"			{
				log("found LCB\n");
				return token::LCB;
			}

"}"			{
				log("found RCB\n");
				return token::RCB;
			}

"("			{
				log("found LB\n");
				return token::LB;
			}

")"			{
				log("found RB\n");
				return token::RB;
			}

","			{
				log("found: COMMA\n");
				return token::COMMA;
			}

"="			{
				log("found: EQUAL\n");
				return token::EQUAL;
			}

"*"			{
				log("found: STAR\n");
				return token::STAR;
			}


<C_CODE,C_CONDITION>"/*"    { tmp_str += std::string(yytext); yy_push_state(C_COMMENT); }

<C_COMMENT>[^*\n]*			{ tmp_str += std::string(yytext);}
<C_COMMENT>"*"+[^*/\n]*		{ tmp_str += std::string(yytext); }
<C_COMMENT>\n   			{ ++line; yylloc->begin.line++; tmp_str += std::string(yytext); }
<C_COMMENT>"*"+"/"			{ tmp_str += std::string(yytext); yy_pop_state(); }

<C_CODE,C_CONDITION>"//".*	{ tmp_str += std::string(yytext); }


<C_CODE,C_CONDITION>.		{ tmp_str += std::string(yytext); }
<C_CODE,C_CONDITION>\n		{ ++line; yylloc->begin.line++; tmp_str += std::string(yytext); }



"/*"   						{ 
								yy_push_state(FSML_COMMENT); 
								log("removing comment\n"); 
							}
<FSML_COMMENT>[^*\n]*		
<FSML_COMMENT>"*"+[^*/\n]*	
<FSML_COMMENT>\n   			{ ++line; yylloc->begin.line++; }
<FSML_COMMENT>"*"+"/"		{ yy_pop_state(); }
"//".*   					{ log("removing comment\n"); }


<<EOF>>						{yyterminate();}

\n							{ ++line; yylloc->begin.line++; }

[[:blank:]]+				{ /* skip silently */ }
.							{ throw FSML::FSMLParser::syntax_error(*yylloc, "invalid character: " + std::string(yytext)); }

%%

#ifndef yywrap
int yywrap() 
{
	return 1;
}
#endif

void FSMLDriver::scanBegin()
{
	std::string msg; 
	if(!(yyin = fopen(filename_.c_str(), "r"))){
		msg += std::string("error opening ") + filename_ + std::string(": ") + strerror(errno);
		error(msg);
	}
}

void FSMLDriver::scanEnd()
{
	fclose(yyin);
	YY_FLUSH_BUFFER;
}

