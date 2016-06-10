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

/**
 * Temporary function to read a number of characters from the files.
 */
std::string FileReader::get_string (int num_chars) {
    // The number of characters read so far.
    int chars_so_far = 0;
    
    // Construct a string of the size specified by the parameter.
    std::string ret = std::string(num_chars, '\0');
    for (char& c: ret) {
        if (chars_so_far >= num_chars) {
            break;
        }

        if ((this->fs).get(c)) {
            // If a character is read successfully from the file stream
            // into the string then increment the number of characters
            // read so far.
            chars_so_far++;
        }
    }

    return ret;
}