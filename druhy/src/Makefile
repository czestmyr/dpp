OBJECTS=StringParser.o ArgumentParser.o types/Integer.o Value.o OptionSyntax.o ArgumentData.o ArgumentException.o FrontEnd.o
CXXFLAGS=-g

.PHONY : all

all: arglib.a

arglib.a: ${OBJECTS}
	ar cq $@ $^

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${OBJECTS}

