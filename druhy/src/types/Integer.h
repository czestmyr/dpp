#ifndef _ARGLIB_INTEGER_TYPE_H_
#define _ARGLIB_INTEGER_TYPE_H_

// TODO: include value header, check method names...

#include "../IType.h"

class Integer: public IType {
	public:
		Integer();
		void setLowBound(int bound);
		void setHighBound(int bound);

		Value fromString(const std::string& argument) const;

	private:
		bool hasLowBound;
		bool hasHighBound;
		int lowBound;
		int highBound;
};

#endif
