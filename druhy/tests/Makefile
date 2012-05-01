OBJECTS=main.o TestCases.o Tests.o
NAME=arglib_test
CXXFLAGS=-I../src
.PHONY : all

all: ${NAME}

run:
	./${NAME}

${NAME}: ${OBJECTS}
	g++ $^ ../src/arglib.a -o $@

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJECTS} ${NAME}

