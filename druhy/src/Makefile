OBJECTS=StringParser.o ArgumentParser.o types/Integer.o Value.o OptionSyntax.o ArgumentData.o ArgumentException.o FrontEnd.o
NAME=arglib.a
CXXFLAGS=-g

.PHONY : all

all: ${NAME}

${NAME}: ${OBJECTS}
	ar cq $@ $^

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${OBJECTS} ${NAME}

