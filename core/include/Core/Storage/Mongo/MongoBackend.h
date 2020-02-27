#ifndef VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
#define VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H

#include <string>
#include <maze/object.h>
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

					virtual void insert(std::string database, std::string collection, std::string value);
					virtual std::string find(std::string database, std::string collection, std::string query);
					virtual void update(std::string database, std::string collection, std::string query, std::string new_value);
					virtual void remove(std::string database, std::string collection, std::string query);

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
