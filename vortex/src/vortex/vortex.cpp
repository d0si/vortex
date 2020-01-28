#include <vortex/vortex.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <maze/object.h>
#include <maze/array.h>
#include <server/http/http_server.h>

namespace vortex {

maze::object config;

void start_vortex(std::vector<std::string> args) {
  for (size_t i = 1; i < args.size(); ++i) {
    if (args[i] == "help" || args[i] == "--help" || args[i] == "-h") {
      show_help();
      return;
    }
  }

  if (args.size() <= 1) {
    // No additional arguments were supplied
  } else if (args[1] == "start") {
    bool errors_detected = false;
    int port = 8080;
    std::string address = "0.0.0.0";

    if (args.size() > 2) {
      for (size_t i = 2; i < args.size(); ++i) {
        std::string arg = args[i];
        bool arg_has_error = false;

        if (arg.length() > 2) {
          if (arg.find("-p=") != std::string::npos || arg.find("--port=") != std::string::npos) {
            size_t equals_pos = arg.find('=');
            std::string port_str = arg.substr(equals_pos + 1, arg.length() - equals_pos);

            try {
              port = std::stoi(port_str);
            } catch (std::invalid_argument) {
              std::cout << "Invalid port: " << port_str << std::endl;
              arg_has_error = true;
            }
          } else if (arg.find("-a=") != std::string::npos || arg.find("--address=") != std::string::npos) {
            size_t equals_pos = arg.find('=');
            std::string address_str = arg.substr(equals_pos + 1, arg.length() - equals_pos);

            address = address_str;
          } else {
            arg_has_error = true;
          }
        } else {
          arg_has_error = true;
        }

        if (arg_has_error) {
          std::cout << "Invalid syntax for argument: " << arg << std::endl;
          errors_detected = true;
        }
      }
    } else {
      
    }

    if (errors_detected) {
      std::cout << "Errors were detected. Aborting..." << std::endl;
      exit(1);
    } else {
      std::cout << "Port: " << port << std::endl << "Address: " << address << std::endl;
    }

  } else if (args[1] == "console") {
    start_console();
  }
}

void show_help() {
  std::cout << "Vortex Help" << std::endl
    << " Usage: ./vortex [command] [--arg1=val1 ...]" << std::endl
    << std::endl
    << std::endl
    << " Available commands:" << std::endl
    << "  (empty)        Tries to run the vortex servers from config file" << std::endl
    << "    --config=[path/to/config.json]" << std::endl
    << "    -c=[path/to/config.json]     Default: server_config.json" << std::endl
    << std::endl
    << "  start          Starts the vortex server" << std::endl
    << "    --port=[port]" << std::endl
    << "    -p=[port]                    Default: 8080" << std::endl
    << "    --address=[ip]" << std::endl 
    << "    -a=[ip]                      Default: 127.0.0.1" << std::endl
    << "    --thread_count=[num]" << std::endl
    << "    -t=[num]                     Default: 4" << std::endl
    << std::endl
    << "  console        Starts vortex shell in interactive mode" << std::endl
    << std::endl
    << "  help           Displays help" << std::endl;
}

void start_console() {
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
    } else if (str == "help") {
      show_help();
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
