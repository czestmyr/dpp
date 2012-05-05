OBJECTS=main.o UseCases.o Tests.o ShortOptionTests.o IntegerTests.o ArgList.o StringTests.o
NAME=arglib_test
CXXFLAGS=-I../src -DCOLORS
# Change CXXFLAGS to following if your shell does not support colors
#CXXFLAGS=-I../src
.PHONY : all

all: ${NAME}

run:
	./${NAME}

${NAME}: ${OBJECTS}
	g++ $^ ../src/arglib.a -o $@

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJECTS}

