#  
#        @file  Makefile
#       @brief  
# 
#      @author  Niccolo` Battezzati, niccolo.battezzati@yahoo.com
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

# build
fsmlc:
	$(MAKE) -C src

.PHONY: examples
examples:
	$(MAKE) -C examples

all: fsmlc examples


# cleaning
clean:
	$(MAKE) clean -C src

clean_examples:
	$(MAKE) clean -C examples



# parser
# ATTENTION: in order to build the parser you need to have in the path
#            both Flex and Bison (>3.0)
parser:
	$(MAKE) parser -C src

clean_parser:
	$(MAKE) clean_parser -C src