#ifndef VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
#define VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H

#include <string>
#include <Core/Storage/IStorageBackend.h>
#include <Core/Storage/Mongo/Mongo.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				class MongoBackend : public Core::Storage::IStorageBackend {
				private:
					Core::Storage::Mongo::Mongo client_;

				public:
					MongoBackend();
					~MongoBackend();

					// Simple query
					virtual void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value);
					virtual std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query);
					virtual std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query);
					virtual void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value);
					virtual void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query);
					virtual void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query);

					// virtual void insert(std::string database, std::string collection, std::string value);
					// virtual std::string find(std::string database, std::string collection, std::string query);
					// virtual void update(std::string database, std::string collection, std::string query, std::string new_value);
					// virtual void remove(std::string database, std::string collection, std::string query);

					virtual std::vector<std::string> get_database_list();
					virtual std::vector<std::string> get_collection_list(const std::string& database);

					virtual bool database_exists(const std::string& database);
					virtual bool collection_exists(const std::string& database, const std::string& collection);

					Core::Storage::Mongo::Mongo* get_client();
				};

				Core::Storage::IStorageBackend* get_mongo_backend();

				static const Core::Storage::StorageBackendDetails mongo_exports = {
					"MongoBackend",
					"Mongo",
					get_mongo_backend
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
