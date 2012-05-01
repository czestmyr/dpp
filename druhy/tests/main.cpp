// TODO: create a real main function. Now, it just test things...
#include "Tests.h"

#include <string>
#include <iostream>
using namespace std;

int main(int argc, const char* argv[]) {
	Tests& tests = Tests::inst();
	tests.runTests();
	return 0;
}

