#ifndef MD5FILEHASHER_H
#define MD5FILEHASHER_H

#include <vector>
#include <string>
#include <openssl/md5.h>
#include <boost/iostreams/device/mapped_file.hpp>

namespace md5hasher {

/**
 * Get MD5 hash of a file.
 */
std::string get_hash (const std::string& _file_name) {
    unsigned char hash[MD5_DIGEST_LENGTH];

    // Hash the file contents.
    boost::iostreams::mapped_file_source src(_file_name);
    MD5((unsigned char*)(src.data()), src.size(), hash);

    // Convert the array to a string and return it.
    std::string ret(std::cbegin(hash), std::cend(hash));
    return ret;
}

} /* namespace md5hasher */

#endif /* MD5FILEHASHER_H */