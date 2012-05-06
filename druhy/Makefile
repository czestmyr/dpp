.PHONY : all

all: use_cases run_tests
clean: clean_library clean_tests clean_use_cases

doxy:
	cd doc; doxygen

library:
	cd src; ${MAKE} ${MFLAGS}

tests: library
	cd tests; ${MAKE} ${MFLAGS}

run_tests: tests
	cd tests; ${MAKE} run

use_cases: library
	cd use_cases; ${MAKE} ${MFLAGS}

clean_library:
	cd src; rm arglib.a; ${MAKE} clean

clean_tests:
	cd tests; rm arglib_test; ${MAKE} clean

clean_use_cases:
	cd use_cases; ${MAKE} clean
