#include <core/storage/mongo/collection.h>
#include <bsoncxx/json.hpp>
#include <maze/element.h>

namespace vortex {
namespace core {
namespace storage {
namespace mongo {

collection::collection(mongocxx::collection collection) : collection_(collection) {

}

maze::array collection::find(maze::object query) {
  return find(query.to_json());
}

maze::array collection::find(std::string json_query) {
  maze::array results;

  auto values = collection_.find(bsoncxx::from_json(json_query));
  for (auto it = values.begin(); it != values.end(); it++) {
    results << maze::object::from_json(bsoncxx::to_json(*it));
  }

  return results;
}

maze::object collection::find_by_id(std::string oid) {
  maze::object query;
  query.set("_id", maze::object("$oid", oid));

  return find_one(query);
}

maze::object collection::find_one(maze::object query) {
  return find_one(query.to_json());
}

maze::object collection::find_one(std::string json_query) {
  auto value = collection_.find_one(bsoncxx::from_json(json_query));

  if (value) {
    return maze::object::from_json(bsoncxx::to_json(value.value()));
  }

  return maze::object();
}

void collection::delete_one(maze::object query) {
  delete_one(query.to_json());
}

void collection::delete_one(std::string json_query) {
  collection_.delete_one(bsoncxx::from_json(json_query));
}

void collection::insert_one(maze::object value) {
  insert_one(value.to_json());
}

void collection::insert_one(std::string json_value) {
  collection_.insert_one(bsoncxx::from_json(json_value));
}

void collection::insert_many(maze::array values) {
  std::vector<std::string> json_values;

  for (auto it = values.begin(); it != values.end(); it++) {
    json_values.push_back(it->to_json());
  }

  insert_many(json_values);
}

void collection::insert_many(std::vector<std::string> json_values_array) {
  std::vector<bsoncxx::document::value> bson_values;

  for (auto it = json_values_array.begin(); it != json_values_array.end(); it++) {
    bson_values.push_back(bsoncxx::from_json(*it));
  }

  collection_.insert_many(bson_values);
}

void collection::replace_one(maze::object query, maze::object replacement_value) {
  replace_one(query.to_json(), replacement_value.to_json());
}

void collection::replace_one(std::string json_query, std::string json_replacement_value) {
  collection_.replace_one(bsoncxx::from_json(json_query), bsoncxx::from_json(json_replacement_value));
}

}  // namespace mongo
}  // namespace storage
}  // namespace core
}  // namespace vortex
