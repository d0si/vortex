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

					virtual Storage::Interface::IDatabase get_database(std::string database_name);
					virtual Storage::Interface::ICollection get_collection(std::string database_name, std::string collection_name);
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_MONGOBACKEND_H
