#ifndef MD5FILEHASHER_H
#define MD5FILEHASHER_H

#include <vector>

class MD5FileHasher {
public:
    static std::vector<unsigned char> get_md5_hash (const std::string&);
};

#endif /* MD5FILEHASHER_H */