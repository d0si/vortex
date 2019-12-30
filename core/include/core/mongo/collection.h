#ifndef VORTEX_CORE_MONGO_COLLECTION_H
#define VORTEX_CORE_MONGO_COLLECTION_H

#include <string>
#include <mongocxx/collection.hpp>
#include <maze/maze_array.h>
#include <maze/maze_object.h>

namespace vortex {
namespace core {
namespace mongo {

class collection {
 private:
  mongocxx::collection collection_;

 public:
  collection(mongocxx::collection collection);

  maze::maze_array find(maze::maze_object query);
  maze::maze_array find(std::string json_query);
  maze::maze_object find_by_id(std::string oid);
  maze::maze_object find_one(maze::maze_object query);
  maze::maze_object find_one(std::string json_query);

  void delete_one(maze::maze_object query);
  void delete_one(std::string json_query);

  void insert_one(maze::maze_object value);
  void insert_one(std::string json_value);

  void insert_many(maze::maze_array values);
  void insert_many(std::vector<std::string> json_values_array);
  void insert_many(std::string json_values);

  void replace_one(maze::maze_object query, maze::maze_object replacement_value);
  void replace_one(std::string json_query, std::string json_replacement_value);
};

}  // namespace mongo
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_MONGO_COLLECTION_H
