// TODO: create a real main function. Now, it just test things...
#include "types/Integer.h"
#include "ArgumentParser.h"
#include "OptionSyntax.h"
#include "ArgumentList.h"
#include "types/Integer.h"

#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	string a, b, c, d, e;
	Integer i;

	OptionSyntax s;

	s.addOption("v");
	s.addOption("version");
	Integer* integer = new Integer;
	integer->setHighBound(100);
	integer->setLowBound(0);
	s.addOption("percent", REQUIRED, integer, "Help for the integer option");

	ArgumentList al;
	ArgumentParser p(&s, &al);
	p.parse(argc, argv);

	return 0;
}
