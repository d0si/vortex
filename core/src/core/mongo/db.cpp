#include <core/mongo/db.h>

namespace vortex {
namespace core {
namespace mongo {

db::db(mongocxx::database database) : database_(database) {

}

collection db::get_collection(std::string collection_name) {
  return collection(database_[collection_name]);
}

std::vector<std::string> db::list_collections() {
  std::vector<std::string> collections;

  auto colls = database_.list_collections();
  for (auto it = colls.begin(); it != colls.end(); it++) {
    collections.push_back((*it)["name"].get_utf8().value.to_string());
  }

  return collections;
}

void db::drop_database() {
  database_.drop();
}

}  // namespace mongo
}  // namespace core
}  // namespace vortex
