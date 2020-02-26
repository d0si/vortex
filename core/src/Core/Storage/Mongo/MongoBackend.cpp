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

				}

				std::string MongoBackend::find(std::string database, std::string collection, std::string query) {
					return "";
				}

				void MongoBackend::update(std::string database, std::string collection, std::string query, std::string new_value) {

				}

				void MongoBackend::remove(std::string database, std::string collection, std::string query) {

				}

				Storage::Interface::IBackend* get_backend() {
					static MongoBackend instance;
					return &instance;
				}
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
