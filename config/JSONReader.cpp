#include "JSONReader.h"

void JSONReader::read_file (const std::string& _file_name) {
    try {
        bpt::read_json(_file_name, this->json_tree);
    } catch (bpt::ptree_error& e) {
        // Catch errors arising from reading the json.
        throw e;
    }
}