CCXX = g++-4.5
CXXFLAGS = -Wall -O2 -std=c++0x
LDFLAGS = 
BINARY = options_test

SOURCES = \
	main.cpp \
	common.cpp \
	option.cpp \
	option_parser.cpp \
	option_category.cpp 

OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))

.PHONY: all clean

all: $(OBJECTS)
	$(CCXX) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

clean:
	rm -f $(OBJECTS)
	rm -f $(BINARY)

## Patterns
%.o: %.cpp
	$(CCXX) $(CXXFLAGS) -c -o $@ $<
