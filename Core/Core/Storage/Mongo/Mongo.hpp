#pragma once

#include <string>
#include <vector>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/client.hpp>
#endif
#include <Maze/Maze.hpp>
#include <Core/Storage/Mongo/Db.hpp>
#include <Core/Storage/Mongo/Collection.hpp>

namespace Vortex::Core::Storage::Mongo {

	class Mongo {
	public:
		VORTEX_CORE_API Mongo();
		VORTEX_CORE_API Mongo(const Maze::Element& mongo_config);

		VORTEX_CORE_API void connect();
		VORTEX_CORE_API void set_config(const Maze::Element& mongo_config);

		VORTEX_CORE_API std::string get_connection_uri();
		VORTEX_CORE_API std::string get_default_db_name();

		VORTEX_CORE_API Db get_db(const std::string& database_name);
		VORTEX_CORE_API Collection get_collection(const std::string& collection_name);
		VORTEX_CORE_API Collection get_collection(const std::string& database_name, const std::string& collection_name);

		VORTEX_CORE_API std::vector<std::string> list_databases();
		VORTEX_CORE_API std::vector<std::string> list_collections(const std::string& database_name);

		VORTEX_CORE_API bool database_exists(const std::string& database);
		VORTEX_CORE_API bool collection_exists(const std::string& database, const std::string& collection);

		VORTEX_CORE_API void drop_database(const std::string& database_name);
		VORTEX_CORE_API void clone_database(const std::string& old_name, const std::string& new_name);

		VORTEX_CORE_API const bool is_enabled() const;

	private:
#ifdef VORTEX_HAS_FEATURE_MONGO
		mongocxx::client _client;
#endif
		Maze::Element _mongo_config;
		bool _enabled = true;
	};

}  // namespace Vortex::Core::Storage::Mongo
