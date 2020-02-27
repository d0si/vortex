#include <Vortex/Vortex.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <maze/object.h>
#include <maze/array.h>
#include <Server/Http/HttpServer.h>
#include <Core/Util/String.h>
#include <boost/filesystem.hpp>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/instance.hpp>
#endif

namespace Util = Vortex::Core::Util;

namespace Vortex {

	void start_vortex(std::vector<std::string> args) {
#ifdef VORTEX_HAS_FEATURE_MONGO
		mongocxx::instance instance{};
#endif

		for (size_t i = 1; i < args.size(); ++i) {
			if (args[i] == "help" || args[i] == "--help" || args[i] == "-h") {
				show_help();
				return;
			}
		}

		if (args.size() <= 1) {
			// No additional arguments were supplied
			start_from_config("server_config.json");

		}
		else if (args[1] == "start") {
			bool errors_detected = false;

			int port = 8080;
			std::string address = "0.0.0.0";
			std::string data_dir = "";
			int thread_count = 4;
			std::string type = "http";

			if (args.size() > 2) {
				for (size_t i = 2; i < args.size(); ++i) {
					std::string arg = args[i];
					bool arg_has_error = false;

					if (arg.length() > 2) {
						if (Util::String::starts_with(arg, "-p=") || Util::String::starts_with(arg, "--port=")) {
							std::vector<std::string> val = Util::String::split(arg, "=");

							try {
								port = std::stoi(val[1]);
							}
							catch (std::invalid_argument) {
								arg_has_error = true;
							}
						}
						else if (Util::String::starts_with(arg, "-a=") || Util::String::starts_with(arg, "--address=")) {
							std::vector<std::string> val = Util::String::split(arg, "=");

							try {
								address = val[1];
							}
							catch (std::invalid_argument) {
								arg_has_error = true;
							}
						}
						else if (Util::String::starts_with(arg, "-d=") || Util::String::starts_with(arg, "--data_dir=")) {
							std::vector<std::string> val = Util::String::split(arg, "=");

							try {
								data_dir = val[1];
							}
							catch (std::invalid_argument) {
								arg_has_error = true;
							}
						}
						else if (Util::String::starts_with(arg, "-t=") || Util::String::starts_with(arg, "--thread_count=")) {
							std::vector<std::string> val = Util::String::split(arg, "=");

							try {
								thread_count = stoi(val[1]);
							}
							catch (std::invalid_argument) {
								arg_has_error = true;
							}
						}
						else {
							arg_has_error = true;
						}
					}
					else {
						arg_has_error = true;
					}

					if (arg_has_error) {
						std::cout << "Invalid syntax for argument: " << arg << std::endl;
						errors_detected = true;
					}
				}
			}

			if (errors_detected) {
				exit_with_error(1000);
			}
			else {
				maze::object config, server_config;
				server_config.set("port", port);
				server_config.set("address", address);
				server_config.set("thread_count", thread_count);
				server_config.set("type", type);
				config.set("server", server_config);

				if (data_dir.length() > 0) {
					try {
						boost::filesystem::path path_obj(data_dir);

						if (boost::filesystem::exists(path_obj) && boost::filesystem::is_directory(path_obj)) {
							data_dir = boost::filesystem::canonical(data_dir).string();
							config.set("vortex", maze::object("data_dir", data_dir));
						}
						else {
							std::cout << "Given data_dir path is not a directory." << std::endl;
							exit_with_error(1007);
						}
					}
					catch (boost::filesystem::filesystem_error & e) {
						std::cout << "data_dir filesystem error: " << e.what() << std::endl;
						exit_with_error(1008);
					}
				}

				start_http_server(config);
			}

		}
		else if (args[1] == "console") {
			start_console();
		}
		else if (Util::String::starts_with(args[1], "-c=") || Util::String::starts_with(args[1], "--config=")) {
			std::vector<std::string> val = Util::String::split(args[1], "=");

			std::string config_path;
			try {
				config_path = val[1];
			}
			catch (...) {
				std::cout << "Invalid syntax for argument: " << args[1] << std::endl;
				exit_with_error(1001);
			}

			start_from_config(config_path);
		}
		else {
			std::cout << "Invalid command line arguments. [" << args[1] << std::endl
				<< "Use ./vortex help to find more info on how to use the program." << std::endl;
			exit_with_error(1002);
		}
	}

	void exit_with_error(int error_code) {
		std::cout << "Errors were detected (Code: " << error_code << "). Aborting..." << std::endl;
		exit(error_code);
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
			<< "    --data_dir=[path/to/data]" << std::endl
			<< "    -d=[path/to/data]            Default: (empty)" << std::endl
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
			}
			else if (str == "start") {
				start_server();
			}
			else if (str == "exit" || str == "q" || str == "quit") {
				std::cout << "Exiting Vortex..." << std::endl;
				exit(0);
			}
			else if (str == "help") {
				show_help();
			}
			else {
				std::cout << "'" << str << "' is not valid command. " << std::endl;
			}
		}
	}

	void start_from_config(const std::string& config_file_name) {
		maze::object config;

		std::ifstream config_file(config_file_name);
		if (config_file.is_open()) {
			std::stringstream buffer;
			buffer << config_file.rdbuf();

			try {
				config = maze::object::from_json(buffer.str());
			}
			catch (...) {
				std::cout << "Unable to parse " << config_file_name << "." << std::endl;
				exit_with_error(1003);
			}

			config_file.close();
		}
		else {
			std::cout << "Unable to find " << config_file_name << "." << std::endl;
			exit_with_error(1004);
		}

		if (config.is_array("servers") && !config["servers"].get_array().is_empty()) {
			maze::array servers = config["servers"];

			for (auto it = servers.begin(); it != servers.end(); it++) {
				if (it->is_int()) {
					start_http_server(maze::object("port", it->get_int()));
				}
				else if (it->is_object()) {
					start_http_server(it->get_object());
				}
				else {
					std::cout << "Server config is invalid: "
						<< std::endl
						<< it->to_json()
						<< std::endl;
					exit_with_error(1005);
				}
			}
		}
		else {
			std::cout << "Unable to find any servers to start in config file." << std::endl;
			exit_with_error(1006);
		}
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
				}
				else if (type == "websocket") {
					std::cout << "Websocket server is currently not yet implemented." << std::endl;

					return;
				}
				else if (type == "http") {
					std::thread server_thread(start_http_server, config);
					server_thread.detach();

					return;
				}
				else {
					std::cout << "'" << type << "' server does not exist." << std::endl;

					return;
				}
			}
		}

		std::thread server_thread(start_http_server, config);
		server_thread.detach();
	}

	void start_http_server(maze::object config) {
		Vortex::Server::Http::HttpServer server;

		server.start(config);
	}

}  // namespace Vortex
