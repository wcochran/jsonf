CXX=g++
CXXFLAGS=-g -Wall -ferror-limit=1 -Wno-unused-private-field
ALL=jsonf

all: $(ALL)

JUNK=*.o *~ *.dSYM *.tab.* lex.yy.c* *.gch

clean:
	-rm -rf $(JUNK)

clobber:
	-rm -rf $(JUNK) $(ALL)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

Env.o: Env.cpp Env.h Value.h
Expr.o: Expr.cpp Expr.h 

OBJS=Expr.o Env.o

jsonf: jsonf.ypp jsonf.l $(OBJS)
	bison -d jsonf.ypp
	flex --outfile=lex.yy.cpp jsonf.l 
	$(CXX) $(CXXFLAGS) jsonf.tab.cpp lex.yy.cpp $(OBJS) -o $@

