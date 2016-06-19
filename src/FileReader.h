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
    
    std::string read_up_to (char);

    // Indicates whether any operation on the file (usually opening) has failed.
    bool fail;
    // Indicates whether the file has been read in its entirety.
    bool done_reading;
private:
    std::string get_buffer_of_size (int);
    std::ifstream fs;
};

#endif /* FILEREADER_H */