OBJECTS=main.o StringParser.o ArgumentParser.o types/Integer.o Value.o OptionSyntax.o ArgumentData.o ArgumentException.o FrontEnd.o tests/Tests.o tests/TestCases.o
CXXFLAGS=-g

.PHONY : all

all: arglib_test

arglib_test: ${OBJECTS}
	g++ ${CXXFLAGS} $^ -o $@

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${OBJECTS}

