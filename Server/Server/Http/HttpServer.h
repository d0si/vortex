#ifndef VORTEX_SERVER_HTTP_HTTP_SERVER_H
#define VORTEX_SERVER_HTTP_HTTP_SERVER_H

#include <Maze/Maze.hpp>

namespace Vortex {
	namespace Server {
		namespace Http {
			class HttpServer {
			private:
				Maze::Element config_;

			public:
				void start(const Maze::Element& config);
			};
		}  // namespace Http
	}  // namespace Server
}  // namespace Vortex

#endif  // VORTEX_SERVER_HTTP_HTTP_SERVER_H
