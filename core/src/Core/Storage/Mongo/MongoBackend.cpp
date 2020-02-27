#include <Core/Storage/Mongo/MongoBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				MongoBackend::MongoBackend() {

				}

				MongoBackend::~MongoBackend() {

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
