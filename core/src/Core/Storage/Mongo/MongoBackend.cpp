#include <Core/Storage/Mongo/MongoBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				VORTEX_STORAGE_BACKEND(MongoBackend, "Mongo")

				MongoBackend::MongoBackend() {

				}

				MongoBackend::~MongoBackend() {

				}

				Storage::Interface::IDatabase MongoBackend::get_database(std::string database_name) {
					return Storage::Interface::IDatabase();
				}

				Storage::Interface::ICollection MongoBackend::get_collection(std::string database_name, std::string collection_name) {
					return Storage::Interface::ICollection();
				}
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
