#ifndef _ARGLIB_FILE_TYPE_H_
#define _ARGLIB_FILE_TYPE_H_

#include "Arglib.h"

class FileType: public Arglib::Type {
	public:
		FileType();
		~FileType();

		Arglib::Value* fromString(const std::string& argument) const;
		Arglib::Type* clone() const;
	private:
};

#endif
