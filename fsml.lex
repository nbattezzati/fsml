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
/*
#include <stdio.h>
#include <string>
#include <errno.h>


#include "FSMLDriver.h"
#include "fsml.hh" 
#include "fsml_inner.h"


#define yyterminate()	return token::END_OF_FILE

#define FSMLlval 		yylval 


#ifdef DEBUG
#undef DEBUG
#endif

typedef FSML::FSMLParser::token token;
*/



#define DEBUG


#ifdef DEBUG
#define print(...) printf(__VA_ARGS__)
#else
#define print(...)
#endif


int line = 1;		/* line counter */
int cb_cnt = 0;		/* counter for curly braces */
int b_cnt = 0;		/* counter for round brackets */


%}

%option noyywrap nounput batch stack

%x DECL FSM VAR STATE STATE_TYPE UNTIL C_CODE C_CONDITION C_COMMENT



GEN_IDENTIFIER	[a-zA-Z]([a-zA-Z0-9_]*)
STRING			\"[^\"]+\"
INTEGER			[0-9]+
CHARACTER		\'.\'
FLOAT			[0-9]+(\.[0-9]+)*
TYPE_SPECIFIER	("void"|"char"|"short"|"int"|"long"|"float"|"double"|"signed"|"unsgined"|"struct"|"union"|"enum")



%%


"decl"		{
				print("found: DECL\n");
				yy_push_state(DECL);
				// return token::DECL;
			}

<DECL>"{"	{
				print("Beginning C-CODE\n");
				printf("%s", yytext);
				yy_push_state(C_CODE);
			}

<C_CODE>"{"	{
				printf("%s", yytext);
				cb_cnt++;
			}

<C_CODE>"}"	{
				printf("%s", yytext);
				cb_cnt--;
				if (cb_cnt < 0) {
					print("found: C_CODE\n");
					cb_cnt = 0;
					if (yy_top_state() == DECL) {
						yy_pop_state();
					}
					yy_pop_state();
					// TODO: return C_CODE with full content 
				}
			}

"fsm"		{
				print("found: FSM\n");
				yy_push_state(FSM);
				// return token::FSM;
			}
			
<FSM>"{"	{
				print("found: LCB\n");
				// return token::LCB;
			}


<FSM>"}"	{
				print("found: RCB\n");
				yy_pop_state();
				// return token::RCB;
			}

<FSM>"var"	{
				print("found: VAR\n");
				yy_push_state(VAR);
				// return token::VAR;
			}

<FSM>"input"	{
				print("found: INPUT\n");
				yy_push_state(VAR);
				// return token::INPUT;
			}

<FSM>"output"	{
				print("found: OUTPUT\n");
				yy_push_state(VAR);
				// return token::OUTPUT;
			}

<VAR>";"	{
				print("found: SC\n");
				yy_pop_state();
				// return token::SC;
			}

<VAR>{TYPE_SPECIFIER} {
				print("found: TYPE %s\n", yytext);
				// TODO: return type with content
			}

<VAR>{GEN_IDENTIFIER} {
				print("found: IDENTIFIER %s\n", yytext);
				// TODO: return identifier with content
			}

<VAR>"="	{
				print("found: EQUAL\n");
				// return token::EQUAL;
			}

<VAR>"*"	{
				print("found: STAR\n");
				// return token::STAR;
			}

<VAR>{INTEGER} {
				print("found: INTEGER %s\n", yytext);
				// TODO: return integer with content
			}

<VAR>{CHARACTER} {
				print("found: CHARACTER %s\n", yytext);
				// TODO: return character with content
			}

<VAR>{FLOAT} {
				print("found: FLOAT %s\n", yytext);
				// TODO: return float with content
			}

<FSM,UNTIL>"until"	{
				print("found: UNTIL\n");
				yy_push_state(UNTIL);
				// return token::UNTIL;
			}

<UNTIL>"("	{
				print("found LB\n");
				// return token::LB;
			}

<UNTIL>{INTEGER} {
				print("found: INTEGER %s\n", yytext);
				// TODO: return integer with content
			}

<UNTIL>")"	{
				print("found RB\n");
				// return token::RB;
			}

<UNTIL>"{"	{
				print("found LCB\n");
				// return token::LCB;
			}

<UNTIL>"}"	{
				print("found RCB\n");
				// return token::LCB;
			}

<FSM,UNTIL>"state"		{
				print("found: STATE\n");
				yy_push_state(STATE);
				// return token::STATE;
			}

<STATE>"["	{
				print("found: LSB\n");
				yy_push_state(STATE_TYPE);
				// return token::LSB;
			}

<STATE_TYPE>"start" {
				print("found: START\n");
				// return token::START;
			}

<STATE_TYPE>"end" {
				print("found: END\n");
				// return token::END;
			}

<STATE_TYPE>"err" {
				print("found: ERR\n");
				// return token::ERR;
			}

<STATE_TYPE>","	{
				print("found: COMMA\n");
				// return token::COMMA;
			}

<STATE_TYPE>"]"	{
				print("found: RSB\n");
				yy_pop_state();
				// return token::RSB;
			}

<STATE>"{"	{
				print("Beginning C_CODE\n");
				printf("%s", yytext);
				yy_push_state(C_CODE);
			}

<STATE>"on"	{
				print("found: ON\n");
				// return token::ON;
			}

<STATE>"("	{
				print("Beginning C_CONDITION\n");
				printf("%s", yytext);
				yy_push_state(C_CONDITION);
			}

<C_CONDITION>"("	{
				printf("%s", yytext);
				b_cnt++;
			}

<C_CONDITION>")"	{
				printf("%s", yytext);
				b_cnt--;
				if (b_cnt < 0) {
					print("found: C_CONDITION\n");
					b_cnt = 0;
					yy_pop_state();
					// TODO: return C_CONDITION with full content 
				}
			}

<UNTIL,STATE>"go"	{
				print("found: GO\n");
				// return token::GO;
			}

<UNTIL,STATE>"err" {
				print("found: ERR\n");
				// return token::ERR;
			}

<UNTIL,STATE>"retry"	{
				print("found: RETRY\n");
				// return token::RETRY;
			}

<STATE>"out"	{
				print("found: OUT\n");
				// return token::OUT;
			}

<UNTIL,STATE>";"	{
				print("found: SC\n");
				yy_pop_state();
				// return token::SC;
			}



<FSM,STATE,UNTIL>{GEN_IDENTIFIER} {
				print("found: IDENTIFIER %s\n", yytext);
				// TODO: return identifier with content
			}




<C_CODE>"/*"    		{ printf("%s", yytext); yy_push_state(C_COMMENT); }
<C_CONDITION>"/*"    	{ printf("%s", yytext); yy_push_state(C_COMMENT); }

<C_COMMENT>[^*\n]*		{ printf("%s", yytext); }
<C_COMMENT>"*"+[^*/\n]*	{ printf("%s", yytext); }
<C_COMMENT>\n   		{ ++line; printf("%s", yytext); }
<C_COMMENT>"*"+"/"		{ printf("%s", yytext); yy_pop_state(); }

<C_CODE>"//".*			{ printf("%s", yytext); }
<C_CONDITION>"//".*		{ printf("%s", yytext); }



<C_CODE>.				{ printf("%s", yytext); }
<C_CODE>\n				{ ++line; printf("%s", yytext); }
<C_CONDITION>.			{ printf("%s", yytext); }
<C_CONDITION>\n			{ ++line; printf("%s", yytext); }


<<EOF>>					{yyterminate();}

\n						{ print("%s", yytext); ++line; /*yylloc->begin.line++;*/ }




%%

#ifndef yywrap
int yywrap() 
{
	return 1;
}
#endif

/*
void FSMLDriver::scanBegin()
{
	std::string msg; 
	if(!(yyin = fopen(file.c_str(), "r"))){
		msg += std::string("error opening ") + file + std::string(": ") + strerror(errno);
		error(msg);
	}
}

void FSMLDriver::scanEnd()
{
	fclose(yyin);
	YY_FLUSH_BUFFER;
}
*/

int main(int argc, char * argv[])
{
	yylex();
	return 0;
}
