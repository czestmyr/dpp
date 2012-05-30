Tests for "Program options" library from the course "Recommended Programming Practices" at the
                                Charles University in Prague

                                    Cestmir Houska, 2012

Compilation and running:

    BEWARE! The library uses the new C++11 standard. Support for this is a bit problematic in GCC
compilers. I succeeded with GCC-4.5 and failed with GCC-4.4 and GCC-4.6. 

    To compile the tests, just run "make" in this directory. You can then run the tests by typing
"./options_tests". If you want more info, you can provide the program with the "-v" option to
be more verbose on the output.
    The test framework prints a colored info about success/failure of each test together with a
short description of that test. If the test throws an unhandled exception, it is also taken as a
failure.
    If your terminal does not support colored output, just change the Makefile according to the
comment there.

