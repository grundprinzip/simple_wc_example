CC    = clang
CXX   = clang++
CXX   = /usr/lib/gcc-snapshot/bin/g++

EXE = my_wc

CDEBUG = -g -Wall
CXXDEBUG = -g -Wall
CXXSTD = -std=c++11

CXXFLAGS = -O3 -DNDEBUG -g -Wall -ggdb $(CXXSTD)

CXXPROD = 


CPPOBJ = main json_driver json_st
SOBJ =  parser lexer

FILES = $(addsuffix .cpp, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
				 json_parser.tab.cc json_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh json_parser.output parser.o \
				 lexer.o json_lexer.yy.cc $(EXE)\
				 lexer_prod.o parser_prod.o \

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)
	$(CXX) $(CXXFLAGS) $(CXXPROD) -o $(EXE)_prod $(OBJS) parser_prod.o lexer_prod.o $(LIBS)


parser: json_parser.yy
	/usr/local/bin/bison -d -v json_parser.yy
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) -c -o parser.o json_parser.tab.cc
	$(CXX) $(CXXFLAGS) $(CXXPROD) -c -o parser_prod.o json_parser.tab.cc

lexer: json_lexer.ll
	flex -f -ojson_lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) $(CXXDEBUG) -c json_lexer.yy.cc -o lexer.o
	$(CXX)  $(CXXFLAGS) $(CXXPROD) -c json_lexer.yy.cc -o lexer_prod.o


.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

