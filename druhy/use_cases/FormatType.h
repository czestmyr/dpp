#ifndef _ARGLIB_FORMAT_TYPE_H_
#define _ARGLIB_FORMAT_TYPE_H_

#include "Arglib.h"

class FormatType: public Type {
	public:
		FormatType();
		~FormatType();

		Value* fromString(const std::string& argument) const;
		Type* clone() const;
	private:
};

#endif
