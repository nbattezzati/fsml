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


int line = 1;
int cb_cnt = 0;


%}

%option noyywrap nounput batch stack

%x DECL FSM C_CODE C_COMMENT



GEN_IDENTIFIER	[a-zA-Z]([a-zA-Z0-9_]*)
STRING			\"[^\"]+\"
INTEGER			[0-9]+



%%


"decl"		{
				print("found: DECL\n");
				yy_push_state(DECL);
				// return token::DECL;
			}

<DECL>"{"	{
				print("found: LCB_DECL\n");
				yy_push_state(C_CODE);
				// return token::LCB_DECL;
			}

<C_CODE>"{"	{
				print("found: LCB_CODE\n");
				print("%s", yytext);
				cb_cnt++;
				// return token::LCB_CODE;
			}

<C_CODE>"}"	{
				cb_cnt--;
				if (cb_cnt < 0) {
					print("found: RCB_DECL\n");
					cb_cnt = 0;
					yy_pop_state();
					yy_pop_state();
					// return token::RCB_DECL;
				}
				else {
					print("found: RCB_CODE\n");
					print("%s", yytext);
					// return token::RCB_CODE;
				}
			}

"fsm"		{
				print("found: FSM\n");
				yy_push_state(FSM);
				// return token::FSM;
			}

<FSM>"{"	{
				print("found: LCB_FSM\n");
				// return token::LCB_FSM;
			}

<FSM>"var"		{
				print("found: VAR\n");
				// return token::VAR;
			}

<FSM>"input"		{
				print("found: INPUT\n");
				// return token::INPUT;
			}

<FSM>"output"	{
				print("found: OUTPUT\n");
				// return token::OUTPUT;
			}

<FSM>{GEN_IDENTIFIER} {
				print("found: identifier %s\n", yytext);
			}

<FSM>"="	{
				print("found: EQUAL\n");
				// return token::EQUAL;
			}

<FSM>"}"	{
				print("found: RCB_FSM\n");
				// return token::RCB_FSM;
			}


<FSM>"state"		{
				print("found: STATE\n");
				exit(0);
				// return token::STATE;
			}

<FSM>"["			{
				#ifdef DEBUG
				printf("found: LB\n");
				#endif
				// return token::LB;
			}

<FSM>"]"			{
				#ifdef DEBUG
				printf("found: RB\n");
				#endif
				// return token::RB;
			}

<FSM>"on"		{
				#ifdef DEBUG
				printf("found: ON\n");
				#endif
				// return token::ON;
			}

<FSM>"go"		{
				#ifdef DEBUG
				printf("found: GO\n");
				#endif
				// return token::GO;
			}

<FSM>"err"		{
				#ifdef DEBUG
				printf("found: ERR\n");
				#endif
				// return token::ERR;
			}

<FSM>"retry"		{
				#ifdef DEBUG
				printf("found: RETRY\n");
				#endif
				// return token::RETRY;
			}

<FSM>"out"		{
				#ifdef DEBUG
				printf("found: OUT\n");
				#endif
				// return token::OUT;
			}

<FSM>"until"		{
				#ifdef DEBUG
				printf("found: UNTIL\n");
				#endif
				// return token::UNTIL;
			}

<FSM>";"			{
				#ifdef DEBUG
				printf("found: SC\n");
				#endif
				// return token::SC;
			}




<C_CODE>"/*"    		{ print("%s", yytext); yy_push_state(C_COMMENT); }
<C_COMMENT>[^*\n]*		{ print("%s", yytext); }
<C_COMMENT>"*"+[^*/\n]*	{ print("%s", yytext); }
<C_COMMENT>\n   		{ ++line; print("%s", yytext); }
<C_COMMENT>"*"+"/"		{ print("%s", yytext); yy_pop_state(); }

<C_CODE>"//".*			{ print("%s", yytext); }



<C_CODE>.				{ print("%s", yytext); }
<C_CODE>\n				{ ++line; print("%s", yytext); }


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
