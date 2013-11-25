CC    ?= clang
CXX   ?= clang++

EXE = my_wc

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++11

CFLAGS = -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -O0  $(CXXDEBUG) $(CXXSTD)


CPPOBJ = main json_driver
SOBJ =  parser lexer

FILES = $(addsuffix .cpp, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
				 json_parser.tab.cc json_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh json_parser.output parser.o \
				 lexer.o json_lexer.yy.cc $(EXE)\

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)


parser: json_parser.yy
	/usr/local/bin/bison -d -v json_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o json_parser.tab.cc

lexer: json_lexer.l
	flex -ojson_lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c json_lexer.yy.cc -o lexer.o


.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

