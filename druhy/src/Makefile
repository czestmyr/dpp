OBJECTS=main.o StringParser.o ArgumentParser.o types/Integer.o Value.o OptionSyntax.o ArgumentData.o ArgumentException.o FrontEnd.o tests/Tests.o tests/TestCases.o

.PHONY : all

all: arglib_test

arglib_test: ${OBJECTS}
	g++ $^ -o $@

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -f ${OBJECTS}

