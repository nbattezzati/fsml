#  
#        @file  Makefile.am
#       @brief  
# 
#      @author  Niccolo` Battezzati, niccolo.battezzati@gmail.com
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

TARGET_FSMLC = fsmlc
TARGET_EXAMPLES = examples
TARGET_PARSER = parser

CXXFLAGS = -std=c++11 -Wno-deprecated-register 
# CXXFLAGS += -DDEBUG			# uncomment to enable debug logs


######### scanning/parsing commands #######
PREFIX = FSML
SCAN = flex   #-i	-d		# -d --> debug		# -i --> case-insesitiveness
PARSE = bison -d -v  # -t --> debug 		# -v is for verbose (explains conflicts) 

SCANNER_INPUT_CPP = fsml.lex
SCANNER_OUTPUT = fsml.yy.cc

PARSER_INPUT_CPP = fsml.yy
PARSER_OUTPUT_CPP = fsml.cc

HEADERS_GEN = location.hh position.hh stack.hh fsml.hh
############################################



SRCS_CPP = FSMLDriver.cpp FSML2CCompiler.cpp


######### targets ###########
# FSML compiler
$(TARGET_FSMLC):
	g++ -o $(TARGET_FSMLC) $(CXXFLAGS) $(PARSER_OUTPUT_CPP) $(SCANNER_OUTPUT) $(SRCS_CPP) main.cpp

all: $(TARGET_PARSER) $(TARGET_FSMLC) $(TARGET_EXAMPLES)
	

# examples
.PHONY: $(TARGET_EXAMPLES)
$(TARGET_EXAMPLES):
	$(MAKE) -C examples


# scanner/parser
$(TARGET_PARSER): scanner_cpp parser_cpp  

scanner_cpp:
	$(SCAN) $(DEBUG) -P$(PREFIX) -o$(SCANNER_OUTPUT) $(SCANNER_INPUT_CPP)

parser_cpp:
	$(PARSE) -p $(PREFIX) -o $(PARSER_OUTPUT_CPP) $(PARSER_INPUT_CPP)


# cleaning
clean:
	rm -f fsml.output $(TARGET_FSMLC)

clean_examples:
	$(MAKE) clean -C examples

clean_parser: clean
	rm -f $(SCANNER_OUTPUT) $(PARSER_OUTPUT_CPP) $(HEADERS_GEN)

