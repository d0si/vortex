#include <server/http/http_server.h>

int main() {
  maze::maze_object server_params;
  server_params.set("port", (int)8080);

  vortex::server::http::http_server server;

  server.start(server_params);

  return 0;
}
