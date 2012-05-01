#include "ShortOptions.h"

#include "Tests.h"
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
	return true;
}

bool ShortOptions::undefinedShortOptionTest() {
	return true;
}

bool ShortOptions::shortSynonymTest() {
	return true;
}

