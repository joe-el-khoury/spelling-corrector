#include <iostream>

#include "FileReader.h"

/**
 * Opens the file stream.
 */
FileReader::FileReader (const std::string& _file_name) {
	(this->fs).open(_file_name);
	if ((this->fs).fail()) {
		std::cout << "The file <" << _file_name << "> could not be opened." << std::endl;
		(this->fail) = true;
	}
}

/**
 * When the object is destroyed, the stream has to be closed.
 */
FileReader::~FileReader () {
	(this->fs).close();
}