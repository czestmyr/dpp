CCXX = g++
CXXFLAGS = -Wall -O2 -std=c++0x -Isolution -DCOLORS -g
# Change CXXFLAGS to following if your shell does not support colors:
#CXXFLAGS = -Wall -O2 -std=c++0x -Isolution
BINARY = options_tests

SOURCES = main.cpp framework.cpp option_tests.cpp value_tests.cpp category_tests.cpp parsing_tests.cpp restriction_tests.cpp usage_tests.cpp
LIB_SOURCES = solution/common.cpp solution/option_category.cpp solution/option.cpp solution/option_parser.cpp

OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))
LIB_OBJECTS := $(addsuffix .o, $(basename $(LIB_SOURCES)))

.PHONY: all clean

all: $(OBJECTS) $(LIB_OBJECTS)
	$(CCXX) $(LDFLAGS) $(OBJECTS) $(LIB_OBJECTS) -o $(BINARY)

clean:
	rm -f $(OBJECTS)
	rm -f $(LIB_OBJECTS)
	rm -f $(BINARY)

## Patterns
%.o: %.cpp
	$(CCXX) $(CXXFLAGS) -c -o $@ $<

