#include <iostream>

#include "FileReader.h"

/**
 * Opens the file stream.
 */
FileReader::FileReader (const std::string& _file_name) {
    // Set both flags to false.
    this->fail = false;
    this->done_reading = false;

    (this->fs).open(_file_name);
    if ((this->fs).fail()) {
        std::cout << "The file <" << _file_name << "> could not be opened." << std::endl;
        this->fail = true;
        // Hacky, but if opening the file fails then just assume reading is done.
        this->done_reading = true;
    }
}

/**
 * When the object is destroyed, the stream has to be closed.
 */
FileReader::~FileReader () {
    (this->fs).close();
}

/**
 * Reads a number of characters from the file, specified by the buffer size.
 */
std::string FileReader::get_string_of_size (int _buff_size) {
    // The number of characters read so far.
    int chars_so_far = 0;
    
    // Construct a string of the size specified by the parameter.
    std::string ret = std::string(_buff_size, '\0');
    for (char& c: ret) {
        if (chars_so_far >= _buff_size) {
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

/**
 * Reads a bunch of characters up to a certain character.
 */
std::string FileReader::get_string_up_to (char _up_to) {
    // I will check only for end of file, because really that's all I care about.
    // Not a very reliable file reading API haha.
    this->done_reading = (bool)(this->fs).eof();
    if (this->done_reading) {
        return std::string();
    }

    std::string ret;
    std::getline(this->fs, ret, _up_to);
    return ret;
}