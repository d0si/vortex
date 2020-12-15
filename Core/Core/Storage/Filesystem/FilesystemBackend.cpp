#include <Core/Storage/Filesystem/FilesystemBackend.h>
#include <fstream>
#include <sstream>
#include <Core/Exceptions/StorageException.h>
#include <Core/CommonRuntime.h>
#include <Core/Util/String.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#define BOOST_ERROR_CODE_HEADER_ONLY

namespace Vortex::Core::Storage::Filesystem {

    FilesystemBackend::FilesystemBackend() {}

    FilesystemBackend::~FilesystemBackend() {}

    void FilesystemBackend::set_config(const Maze::Element& filesystem_config) {
        _filesystem_config = filesystem_config;

        if (_filesystem_config.is_bool("cache_enabled")) {
            _cache_enabled = _filesystem_config["cache_enabled"].get_bool();
        }

        if (_filesystem_config.is_int("cache_expiry")) {
            _cache_expiry = _filesystem_config["cache_expiry"].get_int();
        }

        if (_filesystem_config.is_bool("in_memory_only")) {
            _in_memory_only = _filesystem_config["in_memory_only"].get_bool();

            if (_in_memory_only) {
                _cache_enabled = _in_memory_only;
                _cache_expiry = 0;
            }
        }
    }

    void FilesystemBackend::simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) {
        Maze::Element collection_data = get_collection_entries(database, collection);

        Maze::Element value;
        try {
            value = Maze::Element::from_json(json_value);
        }
        catch (...) {
            throw Exceptions::StorageException("Unable to parse json value");
        }

        collection_data.push_back(value);

        save_collection_entries(database, collection, collection_data);
    }

    const std::string FilesystemBackend::simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        Maze::Element collection_data = get_collection_entries(database, collection);

        Maze::Element simple_query;
        try {
            simple_query = Maze::Element::from_json(json_simple_query);
        }
        catch (...) {
            throw Exceptions::StorageException("Invalid query syntax");
        }

        Maze::Element query_results(Maze::Type::Array);

        for (const auto& val : collection_data) {
            if (check_if_matches_simple_query(val, simple_query)) {
                query_results.push_back(val);
            }
        }

        return query_results.to_json();
    }

    const std::string FilesystemBackend::simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        Maze::Element collection_data = get_collection_entries(database, collection);

        Maze::Element simple_query;
        try {
            simple_query = Maze::Element::from_json(json_simple_query);
        }
        catch (...) {
            throw Exceptions::StorageException("Invalid query syntax");
        }

        for (const auto& val : collection_data) {
            if (check_if_matches_simple_query(val, simple_query)) {
                return val.to_json();
            }
        }

        return "{}";
    }

    void FilesystemBackend::simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) {
        Maze::Element collection_data = get_collection_entries(database, collection);
        Maze::Element new_collection_data(Maze::Type::Object);

        Maze::Element simple_query;
        try {
            simple_query = Maze::Element::from_json(json_simple_query);
        }
        catch (...) {
            throw Exceptions::StorageException("Invalid query syntax");
        }

        Maze::Element replacement_value;
        try {
            replacement_value = Maze::Element::from_json(replacement_json_value);
        }
        catch (...) {
            throw Exceptions::StorageException("Unable to parse replacement json value");
        }

        bool is_replaced = false;
        for (const auto& val : collection_data) {
            if (!is_replaced && check_if_matches_simple_query(val, simple_query)) {
                new_collection_data.push_back(replacement_value);
                is_replaced = true;
            }
            else {
                new_collection_data.push_back(val);
            }
        }

        save_collection_entries(database, collection, new_collection_data);
    }

    void FilesystemBackend::simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        Maze::Element collection_data = get_collection_entries(database, collection);

        Maze::Element simple_query;
        try {
            simple_query = Maze::Element::from_json(json_simple_query);
        }
        catch (...) {
            throw Exceptions::StorageException("Invalid query syntax");
        }

        for (int i = 0; i < collection_data.count_children(); ++i) {
            Maze::Element value = collection_data[i];

            if (check_if_matches_simple_query(value, simple_query)) {
                collection_data.remove_at(i);
            }
        }

        save_collection_entries(database, collection, collection_data);
    }

    void FilesystemBackend::simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        Maze::Element collection_data = get_collection_entries(database, collection);

        Maze::Element simple_query;
        try {
            simple_query = Maze::Element::from_json(json_simple_query);
        }
        catch (...) {
            throw Exceptions::StorageException("Invalid query syntax");
        }

        for (int i = 0; i < collection_data.count_children(); ++i) {
            Maze::Element value = collection_data[i];

            if (check_if_matches_simple_query(value, simple_query)) {
                collection_data.remove_at(i);

                save_collection_entries(database, collection, collection_data);

                return;
            }
        }
    }

    const std::vector<std::string> FilesystemBackend::get_database_list() {
        const std::string cache_key = "vortex.core.filesystem.database_list";

        if (_cache_enabled) {
            if (CommonRuntime::instance().cache()->exists(cache_key)) {
                return Util::String::split(CommonRuntime::instance().cache()->get(cache_key), ",");
            }
        }

        std::vector<std::string> database_list;

        if (!_filesystem_config.is_string("root_path")) {
            return database_list;
        }

        const std::string storage_databases_path = _filesystem_config["root_path"].get_string();

        if (!boost::filesystem::exists(storage_databases_path) || !boost::filesystem::is_directory(storage_databases_path)) {
            return database_list;
        }

        for (const auto& dir_entry : boost::make_iterator_range(boost::filesystem::directory_iterator(storage_databases_path), {})) {
            if (boost::filesystem::is_directory(dir_entry.status())) {
                std::string dir_name = dir_entry.path().filename().string();

                database_list.push_back(dir_name);
            }
        }

        CommonRuntime::instance().cache()->set(cache_key, Util::String::join(database_list, ","), 15);

        return database_list;
    }

    const std::vector<std::string> FilesystemBackend::get_collection_list(const std::string& database) {
        const std::string cache_key = "vortex.core.filesystem.collection_list." + database;

        if (_cache_enabled) {
            if (CommonRuntime::instance().cache()->exists(cache_key)) {
                return Util::String::split(CommonRuntime::instance().cache()->get(cache_key), ",");
            }
        }

        std::vector<std::string> collection_list;

        if (!_filesystem_config.is_string("root_path")) {
            return collection_list;
        }

        const std::string storage_collections_path = _filesystem_config["root_path"].get_string() + "/" + database;

        if (!boost::filesystem::exists(storage_collections_path) || !boost::filesystem::is_directory(storage_collections_path)) {
            return collection_list;
        }

        for (const auto& dir_entry : boost::make_iterator_range(boost::filesystem::directory_iterator(storage_collections_path), {})) {
            if (!boost::filesystem::is_directory(dir_entry.status())) {
                std::string file_name = dir_entry.path().filename().string();

                if (Util::String::ends_with(file_name, ".json")) {
                    std::string name = file_name.substr(0, file_name.length() - 5);

                    collection_list.push_back(name);
                }
            }
        }

        CommonRuntime::instance().cache()->set(cache_key, Util::String::join(collection_list, ","), 15);

        return collection_list;
    }

    bool FilesystemBackend::database_exists(const std::string& database) {
        const std::string cache_key = "vortex.core.filesystem.database_exists." + database;

        if (_cache_enabled) {
            if (CommonRuntime::instance().cache()->exists(cache_key)) {
                return (CommonRuntime::instance().cache()->get(cache_key) == "1");
            }
        }

        std::string database_path = _filesystem_config["root_path"].get_string() + "/" + database;

        if (boost::filesystem::exists(database_path) && boost::filesystem::is_directory(database_path)) {
            if (_cache_enabled) {
                CommonRuntime::instance().cache()->set(cache_key, "1", 15);
            }

            return true;
        }
        else {
            if (_cache_enabled) {
                CommonRuntime::instance().cache()->set(cache_key, "0", 15);
            }

            return false;
        }
    }

    bool FilesystemBackend::collection_exists(const std::string& database, const std::string& collection) {
        const std::string cache_key = "vortex.core.filesystem.collection_exists." + database + "." + collection;

        if (_cache_enabled) {
            if (CommonRuntime::instance().cache()->exists(cache_key)) {
                return (CommonRuntime::instance().cache()->get(cache_key) == "1");
            }
        }

        std::string collection_path = _filesystem_config["root_path"].get_string() + "/" + database + "/" + collection + ".json";

        if (boost::filesystem::exists(collection_path) && boost::filesystem::is_regular_file(collection_path)) {
            if (_cache_enabled) {
                CommonRuntime::instance().cache()->set(cache_key, "1", 15);
            }

            return true;
        }
        else {
            if (_cache_enabled) {
                CommonRuntime::instance().cache()->set(cache_key, "0", 15);
            }

            return false;
        }
    }

    bool FilesystemBackend::check_if_matches_simple_query(const Maze::Element& value, Maze::Element simple_query) const {
        bool value_valid = true;

        for (auto it = simple_query.keys_begin(); it != simple_query.keys_end(); ++it) {
            const std::string key = *it;
            Maze::Element query_part = simple_query[key];

            if (query_part.is_string()) {
                if (!value.exists(key) ||
                    !(value[key].get_string() == query_part.get_string())) {
                    value_valid = false;
                    break;
                }
            }
            else if (query_part.is_bool()) {
                if (!value.exists(key) ||
                    !(value[key].get_bool() == query_part.get_bool())) {
                    value_valid = false;
                    break;
                }
            }
            else if (query_part.is_double()) {
                if (!value.exists(key) ||
                    !(value[key].get_double() == query_part.get_double())) {
                    value_valid = false;
                    break;
                }
            }
            else if (query_part.is_int()) {
                if (!value.exists(key) ||
                    !(value[key].get_int() == query_part.get_int())) {
                    value_valid = false;
                    break;
                }
            }
            else if (query_part.is_array() && key == "$or") {
                bool or_query_valid = false;

                for (const auto& or_query_part : query_part) {
                    if (!or_query_part.is_object()) {
                        throw Exceptions::StorageException("Invalid part of $or query");
                    }

                    if (check_if_matches_simple_query(value, or_query_part)) {
                        or_query_valid = true;
                        break;
                    }
                }

                if (!or_query_valid) {
                    value_valid = false;
                    break;
                }
            }
            else if (query_part.is_object()) {
                if (value.exists(key) && value.is_object(key)) {
                    if (!check_if_matches_simple_query(value[key], query_part)) {
                        value_valid = false;
                        break;
                    }
                }
                else {
                    value_valid = false;
                    break;
                }
            }
            else if (query_part.is_null()) {
                if (value.exists(key) && !value[key].is_null()) {
                    value_valid = false;
                    break;
                }
            }
            else {
                throw Exceptions::StorageException("Invalid query parameter type");
            }
        }

        return value_valid;
    }

    Maze::Element FilesystemBackend::get_collection_entries(const std::string& database, const std::string& collection) const {
        const std::string cache_key = "vortex.core.filesystem.cache." + database + "." + collection;

        if (_cache_enabled) {
            if (CommonRuntime::instance().cache()->exists(cache_key)) {
                return Maze::Element::from_json(CommonRuntime::instance().cache()->get(cache_key));
            }
        }

        if (!_filesystem_config.is_string("root_path")) {
            throw Exceptions::StorageException("Invalid config root_path");
        }

        std::string collection_file_path = _filesystem_config["root_path"].get_string() + '/' + database + '/' + collection + ".json";
        if (!boost::filesystem::exists(collection_file_path)) {
            return Maze::Element(Maze::Type::Array);
        }

        std::ifstream collection_file(collection_file_path);
        if (!collection_file.is_open()) {
            throw Exceptions::StorageException(
                "Unable to open collection file for " + database + "/" + collection);
        }

        std::stringstream value_stream;
        value_stream << collection_file.rdbuf();
        std::string value = value_stream.str();
        collection_file.close();

        Maze::Element collection_data;
        try {
            Maze::Element result = Maze::Element::from_json(value);

            if (_cache_enabled) {
                CommonRuntime::instance().cache()->set(cache_key, value, _cache_expiry);
            }

            return result;
        }
        catch (...) {
            throw Exceptions::StorageException("Collection file is corrupted (unable to parse json)");
        }

        return Maze::Element(Maze::Type::Array);
    }

    void FilesystemBackend::save_collection_entries(const std::string& database, const std::string& collection, const Maze::Element& values) const {
        const std::string cache_key = "vortex.core.filesystem.cache." + database + "." + collection;

        if (_in_memory_only) {
            CommonRuntime::instance().cache()->set(cache_key, values.to_json(0), 0);

            return;
        }

        if (_cache_enabled) {
            CommonRuntime::instance().cache()->set(cache_key, values.to_json(0), _cache_expiry);
        }

        if (!_filesystem_config.is_string("root_path")) {
            throw Exceptions::StorageException("Invalid config root_path");
        }

        std::string database_folder_path = _filesystem_config["root_path"].get_string() + '/' + database;

        if (!boost::filesystem::exists(database_folder_path)) {
            boost::filesystem::create_directory(database_folder_path);
        }

        std::string collection_file_path = database_folder_path + '/' + collection + ".json";

        std::ofstream collection_file(collection_file_path, std::ofstream::trunc);
        if (!collection_file.is_open()) {
            throw Exceptions::StorageException(
                "Unable to open collection file for " + database + "/" + collection);
        }

        collection_file << values.to_json(4);
        collection_file.close();
    }

    StorageBackendInterface* get_filesystem_backend() {
        static FilesystemBackend instance;
        return &instance;
    }

}
