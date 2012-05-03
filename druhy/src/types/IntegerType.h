#ifndef _ARGLIB_INTEGER_TYPE_H_
#define _ARGLIB_INTEGER_TYPE_H_

#include "../Type.h"
#include "../Value.h"

class IntegerType: public Type {
	public:
		IntegerType();
		void setLowBound(int bound);
		void setHighBound(int bound);

		Value* fromString(const std::string& argument) const;
		Type* clone() const;

	private:
		bool hasLowBound;
		bool hasHighBound;
		int lowBound;
		int highBound;
};

#endif
