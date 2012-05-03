#ifndef _ARGLIB_DUMMY_TYPE_H_
#define _ARGLIB_DUMMY_TYPE_H_

#include "../Type.h"
#include "../ArgumentException.h"

using namespace std;

class DummyType: public Type {
	public:
		Value fromString(const string& argument) const {
			throw ArgumentException(string("Option parameter \"") + argument + "\" would have an unspecified type");
		};

		Type* clone() const {
			return new DummyType(*this);
		}
};

#endif

