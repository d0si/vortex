#ifndef VORTEX_CORE_STORAGE_MONGO_DB_H
#define VORTEX_CORE_STORAGE_MONGO_DB_H

#include <string>
#include <vector>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/database.hpp>
#endif
#include <core/storage/mongo/collection.h>

namespace vortex {
	namespace core {
		namespace storage {
			namespace mongo {
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
			}  // namespace mongo
		}  // namespace storage
	}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_DB_H
