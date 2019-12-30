#include <vortex/vortex.h>
#include <mongocxx/instance.hpp>

int main() {
  mongocxx::instance instance{};

  vortex::start_cli();

  return 0;
}
