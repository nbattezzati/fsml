TARGET_FSMLC = fsmlc
TARGET_PARSER = parser

# directory to generate the compiler into
OUTPUT_DIR = ..


CXXFLAGS = -std=c++11 -Wno-deprecated-register 
CXXFLAGS += -Ilib/cxxopts
# CXXFLAGS += -DDEBUG -DYYDEBUG	# uncomment to enable debug logs


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
	g++ -o $(OUTPUT_DIR)/$(TARGET_FSMLC) $(CXXFLAGS) $(PARSER_OUTPUT_CPP) $(SCANNER_OUTPUT) $(SRCS_CPP) main.cpp

all: $(TARGET_PARSER) $(TARGET_FSMLC) $(TARGET_EXAMPLES)
	

# scanner/parser
$(TARGET_PARSER): scanner_cpp parser_cpp  

scanner_cpp:
	$(SCAN) $(DEBUG) -P$(PREFIX) -o$(SCANNER_OUTPUT) $(SCANNER_INPUT_CPP)

parser_cpp:
	$(PARSE) -p $(PREFIX) -o $(PARSER_OUTPUT_CPP) $(PARSER_INPUT_CPP)


# cleaning
clean:
	rm -f fsml.output $(OUTPUT_DIR)/$(TARGET_FSMLC)

clean_parser: clean
	rm -f $(SCANNER_OUTPUT) $(PARSER_OUTPUT_CPP) $(HEADERS_GEN)

