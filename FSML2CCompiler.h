/**
 *       @file  FSML2CCompiler.h
 *      @brief  The declaration of the FSML2CCompiler class, that translates the FSML to C language
 *
 * This file contains the declaration of the FSML2CCompiler class
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


#ifndef FSML2C_COMPILER_H_
#define	FSML2C_COMPILER_H_


#include <string>
#include "FSMLDriver.h"



/**
 * @class FSML2CCompiler
 * @brief The FSML2CCompiler class translates the FSML to C language
 */
class FSML2CCompiler
{

public:
	//public constructor
	FSML2CCompiler(FSMLDriver & fsml) : fsml_(fsml) {}

	//public destructor
	~FSML2CCompiler() {}

	// compile and generate C code
	bool Translate(const std::string & file_name);
	
private:
	std::string CComment(const std::string & msg);
	std::string Translate_FSMLDecl();
	std::string Translate_Decl();
	std::string Translate_TimeOrPeriod();
	std::string Translate_Variables();
	std::string Translate_Timers();
	const std::string kStaticCKeyword_ = "static";
	const std::string kFsmTimerCType_ = "fsm_timer_t";

	const std::string kDefaultOutputCFile_ = "fsm.c";
	const unsigned int kCCommentWidth_ = 59;

	FSMLDriver & fsml_;
};

	
#endif	// FSML2C_COMPILER_H_
