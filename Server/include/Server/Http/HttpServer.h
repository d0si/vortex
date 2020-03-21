#ifndef VORTEX_SERVER_HTTP_HTTP_SERVER_H
#define VORTEX_SERVER_HTTP_HTTP_SERVER_H

#include <Maze/Object.hpp>

namespace Vortex {
	namespace Server {
		namespace Http {
			class HttpServer {
			private:
				Maze::Object config_;

			public:
				void start(Maze::Object config);
			};
		}  // namespace Http
	}  // namespace Server
}  // namespace Vortex

#endif  // VORTEX_SERVER_HTTP_HTTP_SERVER_H
