#include "UseCases.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include <iostream>

using namespace std;

void UseCases::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&UseCases::runShortOptionsTest, "Short option use case (should not throw anything): \"-v -u -p 20\"");
}

bool UseCases::runShortOptionsTest() {
	ArgList args;
	args.push("program").push("-v").push("-u").push("-p").push("20");

	FrontEnd arglib;
	arglib.addOption("v", OPTION_REQUIRED);
	arglib.addSynonym("v", "u");

	IntegerType integer = IntegerType();
	integer.setHighBound(100);
	integer.setLowBound(0);
	arglib.addOption("p", OPTION_ALLOWED, integer, PARAM_REQUIRED);
	arglib.setOptionHelp("p", "Help for the integer option. I want it to be very long so that I can test the automatic line breaking routine that I just created. Hopefully, it will look as good as I suppose. We'll see. If it is not good, I will have to program the line-breaking routine again.");

	cout << endl;
	arglib.writeHelp(cout);

	return Tests::parseMustNotThrow(arglib, args);
}

