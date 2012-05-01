#include "UseCases.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>

using namespace std;

void UseCases::addTestsTo(Tests* testSet) {
	testSet->addTest(&UseCases::runShortOptionsTest, "Short option use case (should not throw anything): \"-v -u -p 20\"");
}

bool UseCases::runShortOptionsTest() {
	ArgList args;
	args.push("program").push("-v").push("-u").push("-p").push("20");

	try {
		FrontEnd arglib;
		arglib.addOption("v");
		arglib.addSynonym("v", "u");

		Integer* integer = new Integer;
		integer->setHighBound(100);
		integer->setLowBound(0);
		arglib.addOption("p", REQUIRED, integer, "Help for the integer option");

		arglib.parse(args.getCount(), args.getArguments());
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return false;
	}

	return true;
}

