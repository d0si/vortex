#include <vortex/vortex.h>
#include <mongocxx/instance.hpp>

int main(int argc, char **args) {
  mongocxx::instance instance{};

  vortex::start_vortex(std::vector<std::string>(args, args + argc));

  return 0;
}
