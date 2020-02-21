#ifndef VORTEX_CORE_STORAGE_MONGO_MONGO_H
#define VORTEX_CORE_STORAGE_MONGO_MONGO_H

#include <string>
#include <vector>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/client.hpp>
#endif
#include <maze/object.h>
#include <core/storage/mongo/db.h>
#include <core/storage/mongo/collection.h>

namespace vortex {
namespace core {
namespace storage {
namespace mongo {

class Mongo {
 private:
#ifdef VORTEX_HAS_FEATURE_MONGO
  mongocxx::client client_;
#endif
  maze::object mongo_config_;
  bool enabled = true;

 public:
  Mongo();
  Mongo(const maze::object& mongo_config);

  void connect();
  void set_config(const maze::object& mongo_config);

  std::string get_connection_uri();
  std::string get_default_db_name();

  Db get_db(std::string database_name);
  Collection get_collection(std::string collection_name);
  Collection get_collection(std::string database_name, std::string collection_name);

  std::vector<std::string> list_databases();
  std::vector<std::string> list_collections(std::string database_name);

  void drop_database(std::string database_name);
  void clone_database(std::string old_name, std::string new_name);
};

}  // namespace mongo
}  // namespace storage
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_MONGO_H
