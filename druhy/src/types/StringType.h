#ifndef _ARGLIB_STRING_TYPE_H_
#define _ARGLIB_STRING_TYPE_H_

#include "../Type.h"
#include "../Value.h"

namespace Arglib {

class StringType: public Type {
	public:
		StringType();
		~StringType() {}

		Value* fromString(const std::string& argument) const;
		Type* clone() const;

	private:
};

} // End namespace Arglib

#endif
