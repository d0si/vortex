#include <Vortex/Vortex.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <Maze/Maze.hpp>
#include <Server/Http/HttpServer.hpp>
#include <Core/Util/String.hpp>
#include <Core/Modules/DependencyInjection.hpp>
#include <Core/Modules/ModuleLoader.hpp>
#include <Core/VortexBase.hpp>
#include <boost/filesystem.hpp>
#ifdef HAS_FEATURE_MONGO
#include <mongocxx/instance.hpp>
#endif

namespace Util = Vortex::Core::Util;

namespace Vortex {
    std::vector<std::thread> running_servers;

    void start_vortex(std::vector<std::string> args) {
#ifdef HAS_FEATURE_MONGO
        mongocxx::instance instance{};
#endif

        for (size_t i = 1; i < args.size(); ++i) {
            if (args[i] == "help" || args[i] == "--help" || args[i] == "-h")
                return show_help();
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
                Maze::Element config(Maze::Type::Object), server_config(Maze::Type::Object);
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
                            config.set("vortex", Maze::Element({ "data_dir" }, { data_dir }));
                        }
                        else {
                            std::cout << "Given data_dir path is not a directory." << std::endl;
                            exit_with_error(1007);
                        }
                    }
                    catch (const boost::filesystem::filesystem_error& e) {
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

        for (size_t i = 0; i < running_servers.size(); ++i) {

            if (running_servers[i].joinable()) {
                running_servers[i].join();
            }
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
        Maze::Element config(Maze::Type::Object);

        std::ifstream config_file(config_file_name);
        if (config_file.is_open()) {
            std::stringstream buffer;
            buffer << config_file.rdbuf();

            try {
                config = Maze::Element::from_json(buffer.str());
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

        if (config.is_array("servers") && config.get("servers").has_children()) {
            const Maze::Element& servers = config.get("servers");

            for (const Maze::Element& server : servers) {
                Maze::Element global_config = config;
                global_config.remove("servers");

                if (server.is_int()) {
                    if (global_config.is_object("server")) {
                        Maze::Element& conf = global_config.get_ref("server");
                        conf.set("port", server.get_int());
                    }
                    else {
                        global_config.set("server", Maze::Element({ "port" }, { server.get_int() }));
                    }

                    running_servers.push_back(std::thread(start_http_server, global_config));
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                else if (server.is_object()) {
                    global_config.apply(server);

                    running_servers.push_back(std::thread(start_http_server, global_config));
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                else {
                    std::cout << "Server config is invalid: "
                        << std::endl
                        << server.to_json()
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
        start_server(Maze::Element(Maze::Type::Object));
    }

    void start_server(const Maze::Element& config) {
        if (config.is_object("server")) {
            const Maze::Element& server_config = config.get("server");

            if (server_config.is_string("type")) {
                const std::string& type = server_config.get("type").s();

                if (type == "https") {
                    std::cout << "Https server is not yet implemented." << std::endl;

                    return;
                }
                else if (type == "websocket") {
                    std::cout << "Websocket server is not yet implemented." << std::endl;

                    return;
                }
                else if (type == "http") {
                    running_servers.push_back(std::thread(start_http_server, config));
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    return;
                }
                else {
                    std::cout << "Server type '" << type << "' does not exist." << std::endl;

                    return;
                }
            }
        }

        running_servers.push_back(std::thread(start_http_server, config));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    using Vortex::Core::Modules::DependencyInjector;
    using Vortex::Core::Modules::Module;
    std::shared_ptr<DependencyInjector> init_di(const Maze::Element& config);

    void start_http_server(const Maze::Element& config) {
        std::shared_ptr<DependencyInjector> program_di = init_di(config);

        Vortex::Server::Http::HttpServer server;

        server.start(config, program_di->di_scope());
    }

    std::shared_ptr<DependencyInjector> init_di(const Maze::Element& config) {
        std::shared_ptr<DependencyInjector> di_scope = DependencyInjector::di_global()->di_scope();

        Maze::Element module_config = config.get("modules");

        // TESTING:
        di_scope->install([](
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Vortex::Core::Applications::string_body_request>& request,
            const std::shared_ptr<Vortex::Core::Applications::string_body_response>& response) {
                return (std::shared_ptr<IApplicationResolver>)std::make_shared<VortexBase::ApplicationResolver>(di, request, response);
            });
        /*
        if (module_config.is_array("load")) {
            for (const auto& module_conf : module_config.get("load")) {
                if (module_conf.is_string()) {
                    std::string module_name = module_conf.get_string();

                    Module* module = di_scope->module_loader()->load_module(module_name);

                    if (module != nullptr) {
                        module->register_di(di_scope);
                    }
                    else {
                        std::cout << "Unable to load module '" << module_name << "'" << std::endl;
                    }
                }
            }
        }
        */
        return di_scope;
    }

}  // namespace Vortex