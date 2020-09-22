all: scanner
	gcc lex.yy.c


scanner:
	flex fsml.lex

clean:
	rm -f lex.yy.c fsml.cc fsml.yy.cc fsml.hh fsml.output location.hh position.hh stack.hh
	rm -f a.out
