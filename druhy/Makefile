.PHONY : all

all: arglib_test

arglib_test: main.o Parser.o types/Integer.o
	g++ $^ -o $@

%.o: %.c
	g++ -c $< -o $@

clean:
	rm -f *.o
	rm -f types/*.o

