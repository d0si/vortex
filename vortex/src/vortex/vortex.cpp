#include <vortex/vortex.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <maze/object.h>
#include <server/http/http_server.h>

namespace vortex {

maze::object config;

void start_cli() {
  load_config();
  apply_config();

  cli_interface();
}

void cli_interface() {
  while (true) {
    std::cout << "Vortex>";

    std::string str;
    std::getline(std::cin, str);

    if (str.length() == 0) {
      continue;
    } else if (str == "start") {
      start_server();
    } else if (str == "exit" || str == "q" || str == "quit") {
      std::cout << "Exiting Vortex..." << std::endl;
      exit(0);
    } else if (str == "save") {
      save_config();
    } else {
      std::cout << "'" << str << "' is not valid command. " << std::endl;
    }
  }
}


void load_config() {
  std::ifstream config_file("server_config.json");
  if (config_file.is_open()) {
    std::stringstream buffer;
    buffer << config_file.rdbuf();

    try {
      config = maze::object::from_json(buffer.str());
    } catch (...) {
      std::cout << "Unable to parse server_config.json." << std::endl;
    }

    config_file.close();
  } else {
    std::cout << "Unable to find server_config.json file." << std::endl;
  }
}

void apply_config() {
  if (config.is_array("servers")) {
    maze::array servers = config["servers"];

    for (auto it = servers.begin(); it != servers.end(); it++) {
      if (it->is_int()) {
        start_server(maze::object("port", it->get_int()));
      } else if (it->is_object()) {
        start_server(it->get_object());
      } else {
        std::cout << "Server config is invalid: "
          << std::endl
          << it->to_json()
          << std::endl;
      }
    }
  }
}

void save_config() {
  std::ofstream config_file("server_config.json", std::ios::out);

  try {
    config_file << config.to_json();
  } catch (...) {
    std::cout << "Unable to write to server_config.json file." << std::endl;
  }

  config_file.close();
}


void start_server() {
  start_server(maze::object());
}

void start_server(maze::object config) {
  if (config.is_object("server")) {
    maze::object server_config = config["server"];

    if (server_config.is_string("type")) {
      std::string type = server_config["type"];

      if (type == "https") {
        std::cout << "Https server is currently not yet implemented." << std::endl;

        return;
      } else if (type == "websocket") {
        std::cout << "Websocket server is currently not yet implemented." << std::endl;

        return;
      } else if (type == "http") {
        std::thread server_thread(start_http_server, config);
        server_thread.detach();

        return;
      } else {
        std::cout << "'" << type << "' server does not exist." << std::endl;

        return;
      }
    }
  }

  std::thread server_thread(start_http_server, config);
  server_thread.detach();
}


void start_http_server(maze::object config) {
  server::http::http_server server;

  server.start(config);
}

}  // namespace vortex
