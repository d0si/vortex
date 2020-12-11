#ifndef VORTEX_CORE_STORAGE_MONGO_COLLECTION_H
#define VORTEX_CORE_STORAGE_MONGO_COLLECTION_H

#include <string>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/collection.hpp>
#endif
#include <Maze/Maze.hpp>

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

					Maze::Element find(const Maze::Element& query);
					Maze::Element find(const std::string& json_query);
					Maze::Element find_by_id(const std::string& oid);
					Maze::Element find_one(const Maze::Element& query);
					Maze::Element find_one(const std::string& json_query);

					void delete_many(const Maze::Element& query);
					void delete_many(const std::string& json_query);
					void delete_one(const Maze::Element& query);
					void delete_one(const std::string& json_query);

					void insert_one(const Maze::Element& value);
					void insert_one(const std::string& json_value);

					void insert_many(const Maze::Element& values);
					void insert_many(const std::vector<std::string>& json_values_array);

					void replace_one(const Maze::Element& query, const Maze::Element& replacement_value);
					void replace_one(const std::string& json_query, const std::string& json_replacement_value);
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_COLLECTION_H
