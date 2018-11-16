#include <fstream>


#include <algorithm>
#include <iostream>
#include <boost/filesystem.hpp>
#include "shared_table.h"
#include "configuration.h"


namespace st_e {

SharedTable& SharedTable::get_instance() {
    static SharedTable instance;
    return instance;
}

std::shared_ptr<Table> SharedTable::get_table(const std::string& name) {
    auto table = cached_tables_.find(name);
    if (table != cached_tables_.end()) {
        return table->second;
    }

    return load_table(name);
}

std::shared_ptr<Table> SharedTable::load_table(const std::string& name) {
//    std::string lowername(name);
//    std::transform(lowername.begin(), lowername.end(), lowername.begin(), ::tolower);
//    fs::path metaDataDirPath(DATA_DIR_PATH);
//    metaDataDirPath /= name;
//    fs::path metaDataFilePath(metaDataDirPath /= name + ".meta");
//
//    if (!fs::exists(metaDataDirPath)) {
//        fs::create_directories(metaDataDirPath);
//    }
//
//    std::ofstream out((metaDataFilePath.root_path().string()));
//    out << "works";
//    out.close();
    return nullptr;
}

} // namespace st_e
