.PHONY : all

all: run_tests
clean: clean_library clean_tests

library:
	cd src; ${MAKE} ${MFLAGS}

tests: library
	cd tests; ${MAKE} ${MFLAGS}

run_tests: tests
	cd tests; ${MAKE} run

clean_library:
	cd src; ${MAKE} clean

clean_tests:
	cd tests; ${MAKE} clean

