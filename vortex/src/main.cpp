#include "server/http/server.h"

int main() {
  vortex::server::http::HttpServer server;
  server.start(8080);

  return 0;
}
