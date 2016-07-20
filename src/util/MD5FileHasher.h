#ifndef MD5FILEHASHER_H
#define MD5FILEHASHER_H

#include <vector>
#include <string>
#include <openssl/md5.h>
#include <boost/iostreams/device/mapped_file.hpp>

namespace MD5FileHasher {

/**
 * Get MD5 hash of a file.
 */
std::vector<unsigned char> get_hash (const std::string& _file_name) {
    unsigned char hash[MD5_DIGEST_LENGTH];

    // Hash the file contents.
    boost::iostreams::mapped_file_source src(_file_name);
    MD5((unsigned char*)(src.data()), src.size(), hash);

    // Convert the array to a vector and return it.
    std::vector<unsigned char> ret(std::begin(hash), std::end(hash));
    return ret;
}

} /* MD5FileHasher */

#endif /* MD5FILEHASHER_H */