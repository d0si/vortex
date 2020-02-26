#ifndef VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
#define VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
#include <string>
#include <Core/Storage/Interface/IBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				class MongoBackend : public Storage::Interface::IBackend {
				public:
					MongoBackend();
					~MongoBackend();

					virtual void insert(std::string database, std::string collection, std::string value);
					virtual std::string find(std::string database, std::string collection, std::string query);
					virtual void update(std::string database, std::string collection, std::string query, std::string new_value);
					virtual void remove(std::string database, std::string collection, std::string query);
				};

				Storage::Interface::IBackend* get_backend();

				Storage::Interface::BackendDetails exports = {
					"MongoBackend",
					"Mongo",
					get_backend
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
