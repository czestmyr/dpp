#include "TestCases.h"

#include "../types/Integer.h"

bool UseCaseShortOptionTest::runTest() {
	FrontEnd h;
	h.addOption("v");
	h.addSynonym("v","u");

	Integer* integer = new Integer;
	integer->setHighBound(100);
	integer->setLowBound(0);
	h.addOption("p", REQUIRED, integer, "Help for the integer option");

	const char* arg1 = "-v";
	const char* arg2 = "-u";
	const char* arg3 = "-p";
	const char* arg4 = "20";
	const char* argv[4];
	argv[0] = arg1;
	argv[1] = arg2;
	argv[2] = arg3;
	argv[3] = arg4;

	h.parse(4,argv);
}
