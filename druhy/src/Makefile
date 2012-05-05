OBJECTS=StringParser.o ArgumentParser.o types/IntegerType.o values/IntValue.o types/StringType.o values/StringValue.o types/BoolType.o values/BoolValue.o types/EnumType.o Value.o OptionSyntax.o ArgumentData.o ArgumentException.o FrontEnd.o ValueHandle.o
NAME=arglib.a
CXXFLAGS=-g

.PHONY : all

all: ${NAME}

${NAME}: ${OBJECTS}
	ar cq $@ $^

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${OBJECTS}

