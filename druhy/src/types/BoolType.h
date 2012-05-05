#ifndef _ARGLIB_BOOL_TYPE_H_
#define _ARGLIB_BOOL_TYPE_H_

#include "../Type.h"
#include "../Value.h"

class BoolType: public Type {
	public:
		BoolType();

		Value* fromString(const std::string& argument) const;
		Type* clone() const;

	private:
};

#endif
