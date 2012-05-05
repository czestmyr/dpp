#include "ShortOptionTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include <iostream>

using namespace std;

void ShortOptionTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&ShortOptionTests::definedShortOptionTest, "Testing whether defined option gets recognized");
	testSet.addTest(&ShortOptionTests::undefinedShortOptionTest, "Testing whether undefined option throws exception");
	testSet.addTest(&ShortOptionTests::shortSynonymTest, "Testing whether synonyms for short options work");
}

bool ShortOptionTests::definedShortOptionTest() {
	ArgList args;
	args.push("program").push("-h");

	FrontEnd arglib;
	arglib.addOption("h");

	return Tests::parseMustNotThrow(arglib, args);
}

bool ShortOptionTests::undefinedShortOptionTest() {
	ArgList args;
	args.push("program").push("-h");

	FrontEnd arglib;
	arglib.addOption("q");

	return Tests::parseMustThrow(arglib, args);
}

bool ShortOptionTests::shortSynonymTest() {
	ArgList args;
	args.push("program").push("-a");

	FrontEnd arglib;
	arglib.addOption("a");
	arglib.addSynonym("a", "b");

	return
		Tests::parseMustNotThrow(arglib, args) &&
		arglib.isOptionSet("b");
}

