// TODO: create a real main function. Now, it just test things...
#include "types/Integer.h"
#include "ArgumentParser.h"

#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	string a, b, c, d, e;
	Integer i;

	a = " - 1235";

	cout << "\"" << a << "\" - " <<
	((i.fromString(a).isValid())?"conforms":"invalid") << endl;
	cout << "The parsed value of a is " << i.fromString(a).getInt() << endl;

	ArgumentParser p;
	p.parse(argc, argv);

	return 0;
}
