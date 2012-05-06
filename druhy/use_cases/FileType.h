#ifndef _ARGLIB_FILE_TYPE_H_
#define _ARGLIB_FILE_TYPE_H_

#include "Arglib.h"

class FileType: public Type {
	public:
		FileType();
		~FileType();

		Value* fromString(const std::string& argument) const;
		Type* clone() const;
	private:
};

#endif
