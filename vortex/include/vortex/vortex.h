#ifndef VORTEX_VORTEX_VORTEX_H
#define VORTEX_VORTEX_VORTEX_H

namespace maze {

class object;

}

namespace vortex {

void start_cli();
void cli_interface();

void load_config();
void apply_config();
void save_config();

void start_server();
void start_server(maze::object config);

void start_http_server(maze::object config);

}  // namespace vortex

#endif  // VORTEX_VORTEX_VORTEX_H
