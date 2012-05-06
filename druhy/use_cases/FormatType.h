#ifndef _ARGLIB_FORMAT_TYPE_H_
#define _ARGLIB_FORMAT_TYPE_H_

#include "Arglib.h"

class FormatType: public Arglib::Type {
	public:
		FormatType();
		~FormatType();

		Arglib::Value* fromString(const std::string& argument) const;
		Arglib::Type* clone() const;
	private:
};

#endif
