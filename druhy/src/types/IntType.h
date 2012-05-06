#ifndef _ARGLIB_INT_TYPE_H_
#define _ARGLIB_INT_TYPE_H_

#include "../Type.h"
#include "../Value.h"

class IntType: public Type {
	public:
		IntType();
		~IntType() {}

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