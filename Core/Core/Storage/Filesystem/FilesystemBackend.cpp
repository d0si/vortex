#include <Core/Storage/Filesystem/FilesystemBackend.h>
#include <fstream>
#include <sstream>
#include <Maze/Array.hpp>
#include <Core/Exception/StorageException.h>
#include <Core/CommonRuntime.h>
#include <Core/Util/String.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace Vortex {
    namespace Core {
        namespace Storage {
            namespace Filesystem {
                FilesystemBackend::FilesystemBackend() {

                }

                FilesystemBackend::~FilesystemBackend() {

                }

                void FilesystemBackend::set_config(const Maze::Object& filesystem_config) {
                    filesystem_config_ = filesystem_config;

                    if (filesystem_config_.is_bool("cache_enabled")) {
                        cache_enabled_ = filesystem_config_["cache_enabled"].get_bool();
                    }

                    if (filesystem_config_.is_int("cache_expiry")) {
                        cache_expiry_ = filesystem_config_["cache_expiry"].get_int();
                    }

                    if (filesystem_config_.is_bool("in_memory_only")) {
                        in_memory_only_ = filesystem_config_["in_memory_only"].get_bool();

                        if (in_memory_only_) {
                            cache_enabled_ = in_memory_only_;
                            cache_expiry_ = 0;
                        }
                    }
                }

                void FilesystemBackend::simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) {
                    Maze::Array collection_data = get_collection_entries(database, collection);

                    Maze::Object value;
                    try {
                        value = Maze::Object::from_json(json_value);
                    }
                    catch (...) {
                        throw Exception::StorageException("Unable to parse json value");
                    }

                    collection_data.push(value);

                    save_collection_entries(database, collection, collection_data);
                }

                std::string FilesystemBackend::simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
                    Maze::Array collection_data = get_collection_entries(database, collection);

                    Maze::Object simple_query;
                    try {
                        simple_query = Maze::Object::from_json(json_simple_query);
                    }
                    catch (...) {
                        throw Exception::StorageException("Invalid query syntax");
                    }

                    Maze::Array query_results;

                    for (auto val : collection_data) {
                        Maze::Object value = val.get_object();

                        if (check_if_matches_simple_query(value, simple_query)) {
                            query_results.push(value);
                        }
                    }

                    return query_results.to_json();
                }

                std::string FilesystemBackend::simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
                    Maze::Array collection_data = get_collection_entries(database, collection);

                    Maze::Object simple_query;
                    try {
                        simple_query = Maze::Object::from_json(json_simple_query);
                    }
                    catch (...) {
                        throw Exception::StorageException("Invalid query syntax");
                    }

                    for (auto val : collection_data) {
                        Maze::Object value = val.get_object();

                        if (check_if_matches_simple_query(value, simple_query)) {
                            return value.to_json();
                        }
                    }

                    return "{}";
                }

                void FilesystemBackend::simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) {
                    Maze::Array collection_data = get_collection_entries(database, collection);
                    Maze::Array new_collection_data;

                    Maze::Object simple_query;
                    try {
                        simple_query = Maze::Object::from_json(json_simple_query);
                    }
                    catch (...) {
                        throw Exception::StorageException("Invalid query syntax");
                    }

                    Maze::Object replacement_value;
                    try {
                        replacement_value = Maze::Object::from_json(replacement_json_value);
                    }
                    catch (...) {
                        throw Exception::StorageException("Unable to parse replacement json value");
                    }

                    bool is_replaced = false;
                    for (auto val : collection_data) {
                        Maze::Object value = val.get_object();

                        if (!is_replaced && check_if_matches_simple_query(value, simple_query)) {
                            new_collection_data.push(replacement_value);
                            is_replaced = true;
                        }
                        else {
                            new_collection_data.push(value);
                        }
                    }

                    save_collection_entries(database, collection, new_collection_data);
                }

                void FilesystemBackend::simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
                    Maze::Array collection_data = get_collection_entries(database, collection);

                    Maze::Object simple_query;
                    try {
                        simple_query = Maze::Object::from_json(json_simple_query);
                    }
                    catch (...) {
                        throw Exception::StorageException("Invalid query syntax");
                    }

                    for (size_t i = 0; i < collection_data.size(); ++i) {
                        Maze::Object value = collection_data[i].get_object();

                        if (check_if_matches_simple_query(value, simple_query)) {
                            collection_data.remove(i);
                        }
                    }

                    save_collection_entries(database, collection, collection_data);
                }

                void FilesystemBackend::simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
                    Maze::Array collection_data = get_collection_entries(database, collection);

                    Maze::Object simple_query;
                    try {
                        simple_query = Maze::Object::from_json(json_simple_query);
                    }
                    catch (...) {
                        throw Exception::StorageException("Invalid query syntax");
                    }

                    for (size_t i = 0; i < collection_data.size(); ++i) {
                        Maze::Object value = collection_data[i].get_object();

                        if (check_if_matches_simple_query(value, simple_query)) {
                            collection_data.remove(i);

                            save_collection_entries(database, collection, collection_data);

                            return;
                        }
                    }
                }

                std::vector<std::string> FilesystemBackend::get_database_list() {
                    const std::string cache_key = "vortex.core.filesystem.database_list";

                    if (cache_enabled_) {
                        if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
                            return Util::String::split(CommonRuntime::Instance.get_cache()->get(cache_key), ",");
                        }
                    }

                    std::vector<std::string> database_list;

                    if (!filesystem_config_.is_string("root_path")) {
                        return database_list;
                    }

                    std::string storage_databases_path = filesystem_config_["root_path"].get_string();

                    if (!boost::filesystem::exists(storage_databases_path) || !boost::filesystem::is_directory(storage_databases_path)) {
                        return database_list;
                    }

                    for (auto dir_entry : boost::make_iterator_range(boost::filesystem::directory_iterator(storage_databases_path), {})) {
                        if (boost::filesystem::is_directory(dir_entry.status())) {
                            std::string dir_name = dir_entry.path().filename().string();

                            database_list.push_back(dir_name);
                        }
                    }

                    CommonRuntime::Instance.get_cache()->set(cache_key, Util::String::join(database_list, ","), 15);

                    return database_list;
                }

                std::vector<std::string> FilesystemBackend::get_collection_list(const std::string& database) {
                    const std::string cache_key = "vortex.core.filesystem.collection_list." + database;

                    if (cache_enabled_) {
                        if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
                            return Util::String::split(CommonRuntime::Instance.get_cache()->get(cache_key), ",");
                        }
                    }

                    std::vector<std::string> collection_list;

                    if (!filesystem_config_.is_string("root_path")) {
                        return collection_list;
                    }

                    std::string storage_collections_path = filesystem_config_["root_path"].get_string() + "/" + database;

                    if (!boost::filesystem::exists(storage_collections_path) || !boost::filesystem::is_directory(storage_collections_path)) {
                        return collection_list;
                    }

                    for (auto dir_entry : boost::make_iterator_range(boost::filesystem::directory_iterator(storage_collections_path), {})) {
                        if (!boost::filesystem::is_directory(dir_entry.status())) {
                            std::string file_name = dir_entry.path().filename().string();

                            if (Util::String::ends_with(file_name, ".json")) {
                                std::string name = file_name.substr(0, file_name.length() - 5);

                                collection_list.push_back(name);
                            }
                        }
                    }

                    CommonRuntime::Instance.get_cache()->set(cache_key, Util::String::join(collection_list, ","), 15);

                    return collection_list;
                }

                bool FilesystemBackend::database_exists(const std::string& database) {
                    const std::string cache_key = "vortex.core.filesystem.database_exists." + database;

                    if (cache_enabled_) {
                        if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
                            return (CommonRuntime::Instance.get_cache()->get(cache_key) == "1");
                        }
                    }

                    std::string database_path = filesystem_config_["root_path"].get_string() + "/" + database;

                    if (boost::filesystem::exists(database_path) && boost::filesystem::is_directory(database_path)) {
                        if (cache_enabled_) {
                            CommonRuntime::Instance.get_cache()->set(cache_key, "1", 15);
                        }

                        return true;
                    }
                    else {
                        if (cache_enabled_) {
                            CommonRuntime::Instance.get_cache()->set(cache_key, "0", 15);
                        }

                        return false;
                    }
                }

                bool FilesystemBackend::collection_exists(const std::string& database, const std::string& collection) {
                    const std::string cache_key = "vortex.core.filesystem.collection_exists." + database + "." + collection;

                    if (cache_enabled_) {
                        if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
                            return (CommonRuntime::Instance.get_cache()->get(cache_key) == "1");
                        }
                    }

                    std::string collection_path = filesystem_config_["root_path"].get_string() + "/" + database + "/" + collection + ".json";
                    
                    if (boost::filesystem::exists(collection_path) && boost::filesystem::is_regular_file(collection_path)) {
                        if (cache_enabled_) {
                            CommonRuntime::Instance.get_cache()->set(cache_key, "1", 15);
                        }

                        return true;
                    }
                    else {
                        if (cache_enabled_) {
                            CommonRuntime::Instance.get_cache()->set(cache_key, "0", 15);
                        }

                        return false;
                    }
                }

                bool FilesystemBackend::check_if_matches_simple_query(const Maze::Object& value, Maze::Object simple_query) const {
                    bool value_valid = true;

                    for (auto query_part : simple_query) {
                        if (query_part.second.is_string()) {
                            if (!value.exists(query_part.first) ||
                                !(value[query_part.first].get_string() == query_part.second.get_string())) {
                                value_valid = false;
                                break;
                            }
                        }
                        else if (query_part.second.is_bool()) {
                            if (!value.exists(query_part.first) ||
                                !(value[query_part.first].get_bool() == query_part.second.get_bool())) {
                                value_valid = false;
                                break;
                            }
                        }
                        else if (query_part.second.is_double()) {
                            if (!value.exists(query_part.first) ||
                                !(value[query_part.first].get_double() == query_part.second.get_double())) {
                                value_valid = false;
                                break;
                            }
                        }
                        else if (query_part.second.is_int()) {
                            if (!value.exists(query_part.first) ||
                                !(value[query_part.first].get_int() == query_part.second.get_int())) {
                                value_valid = false;
                                break;
                            }
                        }
                        else if (query_part.second.is_array() && query_part.first == "$or") {
                            bool or_query_valid = false;

                            for (auto or_query_part : query_part.second.get_array()) {
                                if (!or_query_part.is_object()) {
                                    throw Exception::StorageException("Invalid part of $or query");
                                }

                                if (check_if_matches_simple_query(value, or_query_part.get_object())) {
                                    or_query_valid = true;
                                    break;
                                }
                            }

                            if (!or_query_valid) {
                                value_valid = false;
                                break;
                            }
                        }
                        else if (query_part.second.is_object()) {
                            if (value.exists(query_part.first) && value.is_object(query_part.first)) {
                                if (!check_if_matches_simple_query(value[query_part.first].get_object(), query_part.second.get_object())) {
                                    value_valid = false;
                                    break;
                                }
                            }
                            else {
                                value_valid = false;
                                break;
                            }
                        }
                        else if (query_part.second.is_null()) {
                            if (value.exists(query_part.first) && !value[query_part.first].is_null()) {
                                value_valid = false;
                                break;
                            }
                        }
                        else {
                            throw Exception::StorageException("Invalid query parameter type");
                        }
                    }

                    return value_valid;
                }

                Maze::Array FilesystemBackend::get_collection_entries(const std::string& database, const std::string& collection) const {
                    const std::string cache_key = "vortex.core.filesystem.cache." + database + "." + collection;

                    if (cache_enabled_) {
                        if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
                            return Maze::Array::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
                        }
                    }

                    if (!filesystem_config_.is_string("root_path")) {
                        throw Exception::StorageException("Invalid config root_path");
                    }

                    std::string collection_file_path = filesystem_config_["root_path"].get_string() + '/' + database + '/' + collection + ".json";
                    if (!boost::filesystem::exists(collection_file_path)) {
                        return Maze::Array();
                    }

                    std::ifstream collection_file(collection_file_path);
                    if (!collection_file.is_open()) {
                        throw Exception::StorageException("Unable to open collection file for " + database + "/" + collection);
                    }

                    std::stringstream buffer;
                    buffer << collection_file.rdbuf();
                    collection_file.close();

                    Maze::Array collection_data;
                    try {
                        Maze::Array result = Maze::Array::from_json(buffer.str());

                        if (cache_enabled_) {
                            CommonRuntime::Instance.get_cache()->set(cache_key, buffer.str(), cache_expiry_);
                        }

                        return result;
                    }
                    catch (...) {
                        throw Exception::StorageException("Collection file is corrupted (unable to parse json)");
                    }

                    return Maze::Array();
                }

                void FilesystemBackend::save_collection_entries(const std::string& database, const std::string& collection, const Maze::Array& values) const {
                    const std::string cache_key = "vortex.core.filesystem.cache." + database + "." + collection;

                    if (in_memory_only_) {
                        CommonRuntime::Instance.get_cache()->set(cache_key, values.to_json(0), 0);

                        return;
                    }

                    if (cache_enabled_) {
                        CommonRuntime::Instance.get_cache()->set(cache_key, values.to_json(0), cache_expiry_);
                    }

                    if (!filesystem_config_.is_string("root_path")) {
                        throw Exception::StorageException("Invalid config root_path");
                    }

                    std::string database_folder_path = filesystem_config_["root_path"].get_string() + '/' + database;

                    if (!boost::filesystem::exists(database_folder_path)) {
                        boost::filesystem::create_directory(database_folder_path);
                    }

                    std::string collection_file_path = database_folder_path + '/' + collection + ".json";

                    std::ofstream collection_file(collection_file_path, std::ofstream::trunc);
                    if (!collection_file.is_open()) {
                        throw Exception::StorageException("Unable to open collection file for " + database + "/" + collection);
                    }

                    collection_file << values.to_json(4);
                    collection_file.close();
                }

                Core::Storage::IStorageBackend* get_filesystem_backend() {
                    static FilesystemBackend instance;
                    return &instance;
                }
            }  // namespace Filesystem
        }  // namespace Storage
    }  // namespace Core
}  // namespace Vortex
