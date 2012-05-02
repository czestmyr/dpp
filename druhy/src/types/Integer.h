#ifndef _ARGLIB_INTEGER_TYPE_H_
#define _ARGLIB_INTEGER_TYPE_H_

#include "../IType.h"
#include "../Value.h"

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
