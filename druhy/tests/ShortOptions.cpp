#include "ShortOptions.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include "TestFunction.h"
#include <iostream>

using namespace std;

void ShortOptions::addTestsTo(Tests* testSet) {
	testSet->addTest(&ShortOptions::definedShortOptionTest, "Testing whether defined option gets recognized");
	testSet->addTest(&ShortOptions::undefinedShortOptionTest, "Testing whether undefined option throws exception");
	testSet->addTest(&ShortOptions::shortSynonymTest, "Testing whether synonyms for short options work");
}

bool ShortOptions::definedShortOptionTest() {
	ArgList args;
	args.push("program").push("-h");

	try {
		FrontEnd arglib;
		arglib.addOption("h");
		arglib.parse(args.getCount(), args.getArguments());
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return false;
	}

	return true;
}

bool ShortOptions::undefinedShortOptionTest() {
	ArgList args;
	args.push("program").push("-h");

	try {
		FrontEnd arglib;
		arglib.addOption("q");
		arglib.parse(args.getCount(), args.getArguments());
	} catch (ArgumentException e) {
		cout << "Exception: " <<  e.what();
		return true;
	}

	return false;
}

bool ShortOptions::shortSynonymTest() {
	ArgList args;
	args.push("program").push("-a");

	try {
		FrontEnd arglib;
		arglib.addOption("a");
		arglib.addSynonym("a", "b");
		arglib.parse(args.getCount(), args.getArguments());
		if (!arglib.isOptionSet("b")) {
			return false;
		}
	} catch (ArgumentException e) {
		cout << "Exception: " <<  e.what();
		return false;
	}

	return true;
}

