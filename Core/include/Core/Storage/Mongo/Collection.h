#ifndef VORTEX_CORE_STORAGE_MONGO_COLLECTION_H
#define VORTEX_CORE_STORAGE_MONGO_COLLECTION_H

#include <string>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/collection.hpp>
#endif
#include <Maze/Array.hpp>
#include <Maze/Object.hpp>

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

					Maze::Array find(Maze::Object query);
					Maze::Array find(std::string json_query);
					Maze::Object find_by_id(std::string oid);
					Maze::Object find_one(Maze::Object query);
					Maze::Object find_one(std::string json_query);

					void delete_one(Maze::Object query);
					void delete_one(std::string json_query);

					void insert_one(Maze::Object value);
					void insert_one(std::string json_value);

					void insert_many(Maze::Array values);
					void insert_many(std::vector<std::string> json_values_array);

					void replace_one(Maze::Object query, Maze::Object replacement_value);
					void replace_one(std::string json_query, std::string json_replacement_value);
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_COLLECTION_H
