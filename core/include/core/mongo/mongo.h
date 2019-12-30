#ifndef VORTEX_CORE_MONGO_MONGO_H
#define VORTEX_CORE_MONGO_MONGO_H

#include <string>
#include <vector>
#include <mongocxx/client.hpp>
#include <maze/object.h>
#include <core/mongo/db.h>
#include <core/mongo/collection.h>

namespace vortex {
namespace core {
namespace mongo {

class mongo {
 private:
  mongocxx::client client_;
  maze::object mongo_params_;

 public:
  mongo();
  mongo(maze::object mongo_params);

  std::string get_connection_uri_from_params(maze::object mongo_params);
  std::string get_default_db_name();

  db get_db(std::string database_name);
  collection get_collection(std::string collection_name);
  collection get_collection(std::string database_name, std::string collection_name);

  std::vector<std::string> list_databases();
  std::vector<std::string> list_collections(std::string database_name);

  void drop_database(std::string database_name);
  void clone_database(std::string old_name, std::string new_name);
};

}  // namespace mongo
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_MONGO_MONGO_H
