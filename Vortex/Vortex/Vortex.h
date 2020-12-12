#pragma once

#include <string>
#include <vector>
#include <Maze/Maze.hpp>

namespace Vortex {

	void start_vortex(std::vector<std::string> args);
	void show_help();
	void exit_with_error(int error_code);

	void start_console();
	void start_from_config(const std::string& config_file_name);

	void start_server();
	void start_server(const Maze::Element& config);

	void start_http_server(const Maze::Element& config);

}  // namespace Vortex
