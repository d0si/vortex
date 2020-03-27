#ifndef VORTEX_CORE_STORAGE_MONGO_DB_H
#define VORTEX_CORE_STORAGE_MONGO_DB_H

#include <string>
#include <vector>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/database.hpp>
#endif
#include <Core/Storage/Mongo/Collection.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				class Mongo;

				class Db {
				private:
#ifdef VORTEX_HAS_FEATURE_MONGO
					mongocxx::database database_;
#endif

				public:
					Db();
#ifdef VORTEX_HAS_FEATURE_MONGO
					Db(mongocxx::database database);
#endif

					Collection get_collection(std::string collection_name);

					std::vector<std::string> list_collections();

					void drop_database();
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_DB_H
