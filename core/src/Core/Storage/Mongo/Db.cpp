#include <Core/Storage/Mongo/Db.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				Db::Db() {

				}

#ifdef VORTEX_HAS_FEATURE_MONGO
				Db::Db(mongocxx::database database) : database_(database) {

				}
#endif

				Collection Db::get_collection(std::string collection_name) {
#ifdef VORTEX_HAS_FEATURE_MONGO
					return Collection(database_[collection_name]);
#else
					return Collection();
#endif
				}

				std::vector<std::string> Db::list_collections() {
					std::vector<std::string> collections;

#ifdef VORTEX_HAS_FEATURE_MONGO
					auto colls = database_.list_collections();
					for (auto it = colls.begin(); it != colls.end(); it++) {
						collections.push_back((*it)["name"].get_utf8().value.to_string());
					}
#endif

					return collections;
				}

				void Db::drop_database() {
#ifdef VORTEX_HAS_FEATURE_MONGO
					database_.drop();
#endif
				}
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
