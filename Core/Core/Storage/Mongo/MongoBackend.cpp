#include <Core/Storage/Mongo/MongoBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				MongoBackend::MongoBackend() {

				}

				MongoBackend::~MongoBackend() {

				}

				void MongoBackend::simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) {
					client_.get_collection(database, collection).insert_one(json_value);
				}

				std::string MongoBackend::simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
					return client_.get_collection(database, collection).find(json_simple_query).to_json();
				}

				std::string MongoBackend::simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
					return client_.get_collection(database, collection).find_one(json_simple_query).to_json();
				}
				
				void MongoBackend::simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) {
					client_.get_collection(database, collection).replace_one(json_simple_query, replacement_json_value);
				}

				void MongoBackend::simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
					client_.get_collection(database, collection).delete_many(json_simple_query);
				}

				void MongoBackend::simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
					client_.get_collection(database, collection).delete_one(json_simple_query);
				}

				std::vector<std::string> MongoBackend::get_database_list() {
					return client_.list_databases();
				}

				std::vector<std::string> MongoBackend::get_collection_list(const std::string& database) {
					return client_.list_collections(database);
				}

				bool MongoBackend::database_exists(const std::string& database) {
					return false;
				}

				bool MongoBackend::collection_exists(const std::string& database, const std::string& collection) {
					return false;
				}

				Storage::Mongo::Mongo* MongoBackend::get_client() {
					return &this->client_;
				}

				Storage::IStorageBackend* get_mongo_backend() {
					static MongoBackend instance;
					return &instance;
				}
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
