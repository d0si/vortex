#ifndef VORTEX_VORTEX_VORTEX_H
#define VORTEX_VORTEX_VORTEX_H

#include <string>
#include <vector>

namespace Maze {
	class Object;
}

namespace Vortex {
	void start_vortex(std::vector<std::string> args);
	void show_help();
	void exit_with_error(int error_code);

	void start_console();
	void start_from_config(const std::string& config_file_name);

	void start_server();
	void start_server(Maze::Object config);

	void start_http_server(Maze::Object config);
}  // namespace Vortex

#endif  // VORTEX_VORTEX_VORTEX_H
