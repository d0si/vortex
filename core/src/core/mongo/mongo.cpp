#include <core/mongo/mongo.h>

namespace vortex {
namespace core {
namespace mongo {

mongo::mongo() {
  mongocxx::uri uri{};

  client_ = mongocxx::client{ uri };
}

mongo::mongo(maze::maze_object mongo_params) : mongo_params_(mongo_params) {
  mongocxx::uri uri{ get_connection_uri_from_params(mongo_params) };

  client_ = mongocxx::client{ uri };
}

std::string mongo::get_connection_uri_from_params(maze::maze_object mongo_params) {
  std::string uri = "mongodb://";

  if (mongo_params.is_string("username") && mongo_params.is_string("password")) {
    uri += mongo_params["username"].get_string() + ":" +
           mongo_params["password"].get_string() + "@";
  }

  if (mongo_params.is_string("host")) {
    uri += mongo_params["host"].get_string();
  } else {
    uri += "localhost";
  }

  if (mongo_params.is_int("port")) {
    int port = mongo_params["port"].get_int();

    if (port > 0) {
      uri += ":" + std::to_string(port);
    }
  }

  if (mongo_params.is_string("database")) {
    uri += "/" + mongo_params["database"].get_string();
  }

  return uri;
}

std::string mongo::get_default_db_name() {
  if (mongo_params_.is_string("default_database")) {
    return mongo_params_["default_database"].get_string();
  } else if (mongo_params_.is_string("database")) {
    return mongo_params_["database"].get_string();
  } else {
    return "vortex";
  }
}

db mongo::get_db(std::string database_name) {
  return db(client_[database_name]);
}

collection mongo::get_collection(std::string collection_name) {
  return get_collection(get_default_db_name(), collection_name);
}

collection mongo::get_collection(std::string database_name, std::string collection_name) {
  return collection(client_[database_name][collection_name]);
}

std::vector<std::string> mongo::list_databases() {
  std::vector<std::string> databases;

  auto dbs = client_.list_databases();
  for (auto it = dbs.begin(); it != dbs.end(); it++) {
    databases.push_back((*it)["name"].get_utf8().value.to_string());
  }

  return databases;
}

std::vector<std::string> mongo::list_collections(std::string database_name) {
  db db = get_db(database_name);

  return db.list_collections();
}

void mongo::drop_database(std::string database_name) {
  db db = get_db(database_name);
  db.drop_database();
}

void mongo::clone_database(std::string old_name, std::string new_name) {
  if (old_name == new_name) {
    return;
  }

  db old_db = get_db(old_name);
  db new_db = get_db(new_name);

  std::vector<std::string> collection_list = old_db.list_collections();
  for (auto it = collection_list.begin(); it != collection_list.end(); it++) {
    collection old_collection = old_db.get_collection(*it);
    collection new_collection = new_db.get_collection(*it);

    maze::maze_array old_values = old_collection.find(maze::maze_object());

    new_collection.insert_many(old_values);
  }
}

}  // namespace mongo
}  // namespace core
}  // namespace vortex
