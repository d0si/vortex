#ifndef VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
#define VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H

#include <string>
#include <Core/Storage/Interface/IBackend.h>
#include <Core/Storage/Mongo/Mongo.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				class MongoBackend : public Core::Storage::Interface::IBackend {
				private:
					Core::Storage::Mongo::Mongo client_;

				public:
					MongoBackend();
					~MongoBackend();

					// Simple query
					virtual void simple_insert(std::string database, std::string collection, std::string json_value);
					virtual std::string simple_find_all(std::string database, std::string collection, std::string json_simple_query);
					virtual std::string simple_find_first(std::string database, std::string collection, std::string json_simple_query);
					virtual void simple_replace_first(std::string database, std::string collection, std::string json_simple_query, std::string replacement_json_value);
					virtual void simple_delete_all(std::string database, std::string collection, std::string json_simple_query);
					virtual void simple_delete_first(std::string database, std::string collection, std::string json_simple_query);

					// virtual void insert(std::string database, std::string collection, std::string value);
					// virtual std::string find(std::string database, std::string collection, std::string query);
					// virtual void update(std::string database, std::string collection, std::string query, std::string new_value);
					// virtual void remove(std::string database, std::string collection, std::string query);

					Core::Storage::Mongo::Mongo* get_client();
				};

				Core::Storage::Interface::IBackend* get_backend();

				static const Core::Storage::Interface::BackendDetails exports = {
					"MongoBackend",
					"Mongo",
					get_backend
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
