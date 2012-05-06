OBJECTS=FormatType.o FileType.o
NAME_TIME=test_time
NAME_LS=test_ls
CXXFLAGS=-I../src -DCOLORS
# Change CXXFLAGS to following if your shell does not support colors
#CXXFLAGS=-I../src
.PHONY : all

all: ${NAME_TIME} ${NAME_LS}

${NAME_TIME}: time.o ${OBJECTS}
	g++ $^ ../src/arglib.a -o $@

${NAME_LS}: ls.o ${OBJECTS}
	g++ $^ ../src/arglib.a -o $@

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -rf time.o ls.o ${OBJECTS} ${NAME_LS} ${NAME_TIME}

