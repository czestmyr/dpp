// TODO: create a real main function. Now, it just test things...
#include "types/Integer.h"
#include "ArgumentParser.h"

#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	string a, b, c, d, e;
	Integer i;

	a = "1235";
	b = "   + 1687  ";
	c = "- 345";
	d = "125.862";
	e = "\t\r\n545";

	cout << "\"" << a << "\" - " << ((i.conforms(a))?"conforms":"invalid") << endl;
	cout << "\"" << b << "\" - " << ((i.conforms(b))?"conforms":"invalid") << endl;
	cout << "\"" << c << "\" - " << ((i.conforms(c))?"conforms":"invalid") << endl;
	cout << "\"" << d << "\" - " << ((i.conforms(d))?"conforms":"invalid") << endl;
	cout << "\"" << e << "\" - " << ((i.conforms(e))?"conforms":"invalid") << endl;

	ArgumentParser p;
	p.parse(argc, argv);

	return 0;
}
