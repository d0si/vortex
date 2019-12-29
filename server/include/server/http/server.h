#ifndef VORTEX_SERVER_HTTP_SERVER_H
#define VORTEX_SERVER_HTTP_SERVER_H

#include <maze/MazeObject.h>

namespace vortex {
namespace server {
namespace http {

class HttpServer {
 private:
  maze::MazeObject server_params_;

 public:
  void start(maze::MazeObject server_params);
};

}  // namespace http
}  // namespace server
}  // namespace vortex

#endif  // VORTEX_SERVER_HTTP_SERVER_H
