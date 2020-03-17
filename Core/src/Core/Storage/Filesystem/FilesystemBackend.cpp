#include <Core/Storage/Filesystem/FilesystemBackend.h>
#include <fstream>
#include <sstream>
#include <Maze/Array.hpp>
#include <Core/Exception/StorageException.h>

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
                }

                void FilesystemBackend::simple_insert(std::string database, std::string collection, std::string json_value) {
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

                std::string FilesystemBackend::simple_find_all(std::string database, std::string collection, std::string json_simple_query) {
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

                std::string FilesystemBackend::simple_find_first(std::string database, std::string collection, std::string json_simple_query) {
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

                void FilesystemBackend::simple_replace_first(std::string database, std::string collection, std::string json_simple_query, std::string replacement_json_value) {
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

                void FilesystemBackend::simple_delete_all(std::string database, std::string collection, std::string json_simple_query) {
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

                void FilesystemBackend::simple_delete_first(std::string database, std::string collection, std::string json_simple_query) {
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
                    if (!filesystem_config_.is_string("root_path")) {
                        throw Exception::StorageException("Invalid config root_path");
                    }

                    std::string collection_file_path = filesystem_config_["root_path"].get_string() + '/' + database + '/' + collection + ".json";

                    std::ifstream collection_file(collection_file_path);
                    if (!collection_file.is_open()) {
                        throw Exception::StorageException("Unable to open collection file for " + database + "/" + collection);
                    }

                    std::stringstream buffer;
                    buffer << collection_file.rdbuf();
                    collection_file.close();

                    Maze::Array collection_data;
                    try {
                        return Maze::Array::from_json(buffer.str());
                    }
                    catch (...) {
                        throw Exception::StorageException("Collection file is corrupted (unable to parse json)");
                    }

                    return Maze::Array();
                }

                void FilesystemBackend::save_collection_entries(const std::string& database, const std::string& collection, const Maze::Array& values) const {
                    if (!filesystem_config_.is_string("root_path")) {
                        throw Exception::StorageException("Invalid config root_path");
                    }

                    std::string collection_file_path = filesystem_config_["root_path"].get_string() + '/' + database + '/' + collection + ".json";

                    std::ofstream collection_file(collection_file_path, std::ofstream::trunc);
                    if (!collection_file.is_open()) {
                        throw Exception::StorageException("Unable to open collection file for " + database + "/" + collection);
                    }

                    collection_file << values.to_json(4);
                    collection_file.close();
                }

                Storage::Interface::IBackend* get_backend() {
                    static FilesystemBackend instance;
                    return &instance;
                }
            }  // namespace Filesystem
        }  // namespace Storage
    }  // namespace Core
}  // namespace Vortex
