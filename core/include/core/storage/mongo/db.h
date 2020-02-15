#ifndef VORTEX_CORE_STORAGE_MONGO_DB_H
#define VORTEX_CORE_STORAGE_MONGO_DB_H

#include <string>
#include <vector>
#include <mongocxx/database.hpp>
#include <core/storage/mongo/collection.h>

namespace vortex {
namespace core {
namespace storage {
namespace mongo {

class Mongo;

class Db {
 private:
  mongocxx::database database_;

 public:
  Db(mongocxx::database database);

  Collection get_collection(std::string collection_name);

  std::vector<std::string> list_collections();

  void drop_database();
};

}  // namespace mongo
}  // namespace storage
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_STORAGE_MONGO_DB_H
