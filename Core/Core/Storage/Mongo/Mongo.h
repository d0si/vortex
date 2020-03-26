#ifndef VORTEX_CORE_STORAGE_MONGO_MONGO_H
#define VORTEX_CORE_STORAGE_MONGO_MONGO_H

#include <string>
#include <vector>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/client.hpp>
#endif
#include <Maze/Object.hpp>
#include <Core/Storage/Mongo/Db.h>
#include <Core/Storage/Mongo/Collection.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				class Mongo {
				private:
#ifdef VORTEX_HAS_FEATURE_MONGO
					mongocxx::client client_;
#endif
					Maze::Object mongo_config_;
					bool enabled = true;

				public:
					Mongo();
					Mongo(const Maze::Object& mongo_config);

					void connect();
					void set_config(const Maze::Object& mongo_config);

					std::string get_connection_uri();
					std::string get_default_db_name();

					Db get_db(std::string database_name);
					Collection get_collection(std::string collection_name);
					Collection get_collection(std::string database_name, std::string collection_name);

					std::vector<std::string> list_databases();
					std::vector<std::string> list_collections(std::string database_name);

					void drop_database(std::string database_name);
					void clone_database(std::string old_name, std::string new_name);

					const bool is_enabled() const;
				};
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_MONGO_H
