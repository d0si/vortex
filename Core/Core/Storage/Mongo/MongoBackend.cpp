#include <Core/Storage/Mongo/MongoBackend.h>

namespace Vortex::Core::Storage::Mongo {

    MongoBackend::MongoBackend() {}

    MongoBackend::~MongoBackend() {}

    void MongoBackend::simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) {
        _client.get_collection(database, collection).insert_one(json_value);
    }

    const std::string MongoBackend::simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        return _client.get_collection(database, collection).find(json_simple_query).to_json();
    }

    const std::string MongoBackend::simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        return _client.get_collection(database, collection).find_one(json_simple_query).to_json();
    }

    void MongoBackend::simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) {
        _client.get_collection(database, collection).replace_one(json_simple_query, replacement_json_value);
    }

    void MongoBackend::simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        _client.get_collection(database, collection).delete_many(json_simple_query);
    }

    void MongoBackend::simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
        _client.get_collection(database, collection).delete_one(json_simple_query);
    }

    const std::vector<std::string> MongoBackend::get_database_list() {
        return _client.list_databases();
    }

    const std::vector<std::string> MongoBackend::get_collection_list(const std::string& database) {
        return _client.list_collections(database);
    }

    bool MongoBackend::database_exists(const std::string& database) {
        return false;
    }

    bool MongoBackend::collection_exists(const std::string& database, const std::string& collection) {
        return false;
    }

    Core::Storage::Mongo::Mongo* MongoBackend::get_client() {
        return &_client;
    }

    StorageBackendInterface* get_mongo_backend() {
        static MongoBackend instance;
        return &instance;
    }

}
