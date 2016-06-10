#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader {
public:
	FileReader (const std::string&);
	~FileReader ();
	
	// Copy constructor and assignment operator are deleted functions to prevent
	// copying around of the file stream.
	FileReader (const FileReader&) = delete;
	FileReader& operator= (const FileReader&) = delete;

    std::string get_string_of_size (int);
    std::string get_string_up_to (char);

	// Indicates whether any operation on the file (usually opening) has failed.
	bool fail;
private:
	std::ifstream fs;
};

#endif /* FILEREADER_H */