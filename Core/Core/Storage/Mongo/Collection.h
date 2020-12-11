#pragma once

#include <string>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/collection.hpp>
#endif
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core::Storage::Mongo {

	class Collection {
	public:
		Collection();
#ifdef VORTEX_HAS_FEATURE_MONGO
		Collection(mongocxx::collection collection);
#endif

		VORTEX_CORE_API Maze::Element find(const Maze::Element& query);
		VORTEX_CORE_API Maze::Element find(const std::string& json_query);
		VORTEX_CORE_API Maze::Element find_by_id(const std::string& oid);
		VORTEX_CORE_API Maze::Element find_one(const Maze::Element& query);
		VORTEX_CORE_API Maze::Element find_one(const std::string& json_query);

		VORTEX_CORE_API void delete_many(const Maze::Element& query);
		VORTEX_CORE_API void delete_many(const std::string& json_query);
		VORTEX_CORE_API void delete_one(const Maze::Element& query);
		VORTEX_CORE_API void delete_one(const std::string& json_query);

		VORTEX_CORE_API void insert_one(const Maze::Element& value);
		VORTEX_CORE_API void insert_one(const std::string& json_value);

		VORTEX_CORE_API void insert_many(const Maze::Element& values);
		VORTEX_CORE_API void insert_many(const std::vector<std::string>& json_values_array);

		VORTEX_CORE_API void replace_one(const Maze::Element& query, const Maze::Element& replacement_value);
		VORTEX_CORE_API void replace_one(const std::string& json_query, const std::string& json_replacement_value);

	private:
#ifdef VORTEX_HAS_FEATURE_MONGO
		mongocxx::collection _collection;
#endif
	};

}  // namespace Vortex::Core::Storage::Mongo
