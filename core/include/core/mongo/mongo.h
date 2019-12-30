#ifndef VORTEX_CORE_MONGO_MONGO_H
#define VORTEX_CORE_MONGO_MONGO_H

#include <string>
#include <mongocxx/client.hpp>
#include <maze/maze_object.h>

namespace vortex {
namespace core {
namespace mongo {

class mongo {
 private:
  mongocxx::client client_;
  maze::maze_object mongo_params_;

 public:
  mongo();
  mongo(maze::maze_object mongo_params);

  std::string get_connection_uri_from_params(maze::maze_object mongo_params);
  std::string get_default_db();
};

}  // namespace mongo
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_MONGO_MONGO_H
