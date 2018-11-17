#include <fstream>
#include <algorithm>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <shared_table.h>


#include "shared_table.h"
#include "configuration.h"

namespace fs = boost::filesystem;
namespace st_e {

SharedTable& SharedTable::get_instance() {
    static SharedTable instance;
    return instance;
}

//std::shared_ptr<Table> SharedTable::get_table(const std::string& name) {
//    auto table = cached_tables_.find(name);
//    if (table != cached_tables_.end()) {
//        return table->second;
//    }
//
//    return load_table(name);
//}

Table& SharedTable::load_table(const std::string& name) {
    std::string lowername(name);
    std::transform(lowername.begin(), lowername.end(), lowername.begin(), ::tolower);
    fs::path metaDataDirPath(DATA_DIR_PATH);
    metaDataDirPath /= name;
    fs::path metaDataFilePath(metaDataDirPath /= name + ".meta");

    if (!fs::exists(metaDataDirPath)) {
        fs::create_directories(metaDataDirPath);
    }

    std::ofstream out((metaDataFilePath.root_path().string()));
    out << "works";
    out.close();
    Table l("s", std::vector<Column> {Column(st_e::Column::Type::INT, "ids")});

    return l;
}

void SharedTable::save_table(const Table& table) {
    // first save to disk, then to RAM
    save_to_disk(table);
    cached_tables_.insert_or_assign(table.get_name(), table);
}

void SharedTable::save_to_disk(const Table& table) {
    auto metadata_file_path = get_metadata_file_path(table);
    auto data_dir = metadata_file_path.parent_path();
    // Todo: try-catch
    if (!fs::exists(data_dir)) {
        fs::create_directories(data_dir);
    }

    std::ofstream data_file;
    data_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    data_file.open(metadata_file_path.string());

    for (const auto& column : table.get_columns()) {
        data_file << column.get_type_string() << " " << column.name << '\n';
    }
    data_file.close();
}

fs::path SharedTable::get_metadata_file_path(const Table& table) {
    auto table_name = boost::to_lower_copy(table.get_name());

    // **/{data_dir_path}/{table_name}/{table_name.meta}
    auto meta_data_file_path = fs::current_path() /= fs::path(DATA_DIR_PATH) /= fs::path(table_name)
            /= fs::path(table_name + ".meta");

    return meta_data_file_path.string();
}

} // namespace st_e
