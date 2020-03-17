#include <Core/Storage/Filesystem/FilesystemBackend.h>
#include <fstream>
#include <sstream>
#include <Maze/Array.hpp>

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

                }

                std::string FilesystemBackend::simple_find_all(std::string database, std::string collection, std::string json_simple_query) {
                    return "";
                }

                std::string FilesystemBackend::simple_find_first(std::string database, std::string collection, std::string json_simple_query) {
                    if (!filesystem_config_.is_string("root_path")) {
                        throw std::exception("Invalid root_path");  // TODO
                    }

                    std::string collection_file_path = filesystem_config_["root_path"].get_string() + '/' + database + '/' + collection + ".json";

                    std::ifstream collection_file(collection_file_path);
                    if (!collection_file.is_open()) {
                        std::string error_msg("Unable to open collection file (" + collection + ")");
                        throw std::exception(error_msg.c_str());
                    }

                    std::stringstream buffer;
                    buffer << collection_file.rdbuf();

                    Maze::Array collection_data;
                    try {
                        collection_data = Maze::Array::from_json(buffer.str());
                    }
                    catch (...) {
                        throw std::exception("Collection file is corrupted");
                    }

                    Maze::Object simple_query;
                    try {
                        simple_query = Maze::Object::from_json(json_simple_query);
                    }
                    catch (...) {
                        throw std::exception("Invalid query syntax");
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

                }

                void FilesystemBackend::simple_delete_all(std::string database, std::string collection, std::string json_simple_query) {

                }

                void FilesystemBackend::simple_delete_first(std::string database, std::string collection, std::string json_simple_query) {

                }

                void FilesystemBackend::insert(std::string database, std::string collection, std::string value) {

                }

                std::string FilesystemBackend::find(std::string database, std::string collection, std::string query) {
                    Maze::Array results;

                    if (database == "vortex") {
                        if (collection == "hosts") {
                            Maze::Object host("hostname", "localhost");
                            host.set("app_id", "0");
                            host.set("script", "view.echo('Default host script.')");

                            results.push(host);
                        }
                        else if (collection == "apps") {
                            Maze::Object app("hostname", "localhost");
                            app.set("title", "Default application");
                            app.set("script", "view.echo('Default application script.')");

                            results.push(app);
                        }
                        else if (collection == "controllers") {
                            Maze::Object app("name", "index");
                            app.set("app_ids", Maze::Array().push(0));
                            app.set("script", "view.echo('Default controller script.')");

                            results.push(app);
                        }
                    }

                    return results.to_json();
                }

                void FilesystemBackend::update(std::string database, std::string collection, std::string query, std::string new_value) {

                }

                void FilesystemBackend::remove(std::string database, std::string collection, std::string query) {

                }

                bool FilesystemBackend::check_if_matches_simple_query(const Maze::Object& value, Maze::Object& simple_query) const {
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
                                    throw std::exception("Invalid query or part");
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
                            throw std::exception("Invalid query parameter type");
                        }
                    }

                    return value_valid;
                }

                Storage::Interface::IBackend* get_backend() {
                    static FilesystemBackend instance;
                    return &instance;
                }
            }  // namespace Filesystem
        }  // namespace Storage
    }  // namespace Core
}  // namespace Vortex
