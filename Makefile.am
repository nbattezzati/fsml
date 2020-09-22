#  
#        @file  Makefile.am
#       @brief  
# 
#      @author  Niccolo` Battezzati, niccolo.battezzati@gmail.com
# 
#    @internal
#      Created  01/24/11
#      Company  Politecnico di Torino
#    Copyright  Copyright (c) 2011, Politecnico di Torino
# 
#  This source code is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  This source code is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser Public License for more details.

#  You should have received a copy of the GNU Lesser Public License
#  along with this source code.  If not, see <http://www.gnu.org/licenses/>.
#  =====================================================================================
#  

DEBUG =

######### scanning/parsing commands #######

PREFIX = ACTEL_PDC

SCAN = flex   #-i	-d		# -d --> debug		# -i --> case-insesitiveness
PARSE = bison -d -v	# -t --> debug 		# -v is for verbose (explains conflicts) 

######### files ############

SCANNER_INPUT_CPP = actelPdc.lexpp
SCANNER_OUTPUT = actelPdc.yy.cc


PARSER_INPUT_CPP = actelPdc.yy
PARSER_OUTPUT_CPP = actelPdc.cc

HEADERS_GEN = location.hh position.hh stack.hh actelPdc.hh

SRCS_CPP = ActelPdcDriver.cpp


if FAME_GEN_PARSER

######### rules ###########
all: parser_cpp scanner_cpp 


scanner_cpp:
	$(SCAN) $(DEBUG) -P$(PREFIX) -o$(SCANNER_OUTPUT) $(SCANNER_INPUT_CPP)

parser_cpp:
	$(PARSE) -p $(PREFIX) -o $(PARSER_OUTPUT_CPP) $(PARSER_INPUT_CPP)

clean-local:
	rm -f $(SCANNER_OUTPUT) $(PARSER_OUTPUT_CPP) $(HEADERS_GEN)

endif
