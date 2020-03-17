#include <Core/Storage/Mongo/MongoBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				MongoBackend::MongoBackend() {

				}

				MongoBackend::~MongoBackend() {

				}

				void MongoBackend::simple_insert(std::string database, std::string collection, std::string json_value) {
					client_.get_collection(database, collection).insert_one(json_value);
				}

				std::string MongoBackend::simple_find_all(std::string database, std::string collection, std::string json_simple_query) {
					return client_.get_collection(database, collection).find(json_simple_query).to_json();
				}

				std::string MongoBackend::simple_find_first(std::string database, std::string collection, std::string json_simple_query) {
					return client_.get_collection(database, collection).find_one(json_simple_query).to_json();
				}
				
				void MongoBackend::simple_replace_first(std::string database, std::string collection, std::string json_simple_query, std::string replacement_json_value) {
					client_.get_collection(database, collection).replace_one(json_simple_query, replacement_json_value);
				}

				void MongoBackend::simple_delete_all(std::string database, std::string collection, std::string json_simple_query) {
					client_.get_collection(database, collection).delete_many(json_simple_query);
				}

				void MongoBackend::simple_delete_first(std::string database, std::string collection, std::string json_simple_query) {
					client_.get_collection(database, collection).delete_one(json_simple_query);
				}

				void MongoBackend::insert(std::string database, std::string collection, std::string value) {
					this->client_.get_collection(database, collection)
						.insert_one(value);
				}

				std::string MongoBackend::find(std::string database, std::string collection, std::string query) {
					return this->client_.get_collection(database, collection)
						.find(query)
						.to_json();
				}

				void MongoBackend::update(std::string database, std::string collection, std::string query, std::string new_value) {
					this->client_.get_collection(database, collection)
						.replace_one(query, new_value);
				}

				void MongoBackend::remove(std::string database, std::string collection, std::string query) {
					this->client_.get_collection(database, collection)
						.delete_one(query);
				}

				Storage::Mongo::Mongo* MongoBackend::get_client() {
					return &this->client_;
				}

				Storage::Interface::IBackend* get_backend() {
					static MongoBackend instance;
					return &instance;
				}
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
