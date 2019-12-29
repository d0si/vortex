#ifndef VORTEX_SERVER_HTTP_HTTP_SERVER_H
#define VORTEX_SERVER_HTTP_HTTP_SERVER_H

#include <maze/maze_object.h>

namespace vortex {
namespace server {
namespace http {

class http_server {
 private:
  maze::maze_object server_params_;

 public:
  void start(maze::maze_object server_params);
};

}  // namespace http
}  // namespace server
}  // namespace vortex

#endif  // VORTEX_SERVER_HTTP_HTTP_SERVER_H
