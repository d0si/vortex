#ifndef VORTEX_VORTEX_VORTEX_H
#define VORTEX_VORTEX_VORTEX_H

#include <string>
#include <vector>

namespace maze {
	class object;
}

namespace Vortex {
	void start_vortex(std::vector<std::string> args);
	void show_help();
	void exit_with_error(int error_code);

	void start_console();
	void start_from_config(const std::string& config_file_name);

	void start_server();
	void start_server(maze::object config);

	void start_http_server(maze::object config);
}  // namespace Vortex

#endif  // VORTEX_VORTEX_VORTEX_H
