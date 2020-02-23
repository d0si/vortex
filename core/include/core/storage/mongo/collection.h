#ifndef VORTEX_CORE_STORAGE_MONGO_COLLECTION_H
#define VORTEX_CORE_STORAGE_MONGO_COLLECTION_H

#include <string>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/collection.hpp>
#endif
#include <maze/array.h>
#include <maze/object.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				class Collection {
				private:
#ifdef VORTEX_HAS_FEATURE_MONGO
					mongocxx::collection collection_;
#endif

				public:
					Collection();
#ifdef VORTEX_HAS_FEATURE_MONGO
					Collection(mongocxx::collection collection);
#endif

					maze::array find(maze::object query);
					maze::array find(std::string json_query);
					maze::object find_by_id(std::string oid);
					maze::object find_one(maze::object query);
					maze::object find_one(std::string json_query);

					void delete_one(maze::object query);
					void delete_one(std::string json_query);

					void insert_one(maze::object value);
					void insert_one(std::string json_value);

					void insert_many(maze::array values);
					void insert_many(std::vector<std::string> json_values_array);

					void replace_one(maze::object query, maze::object replacement_value);
					void replace_one(std::string json_query, std::string json_replacement_value);
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_COLLECTION_H
