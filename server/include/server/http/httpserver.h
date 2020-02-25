#ifndef VORTEX_SERVER_HTTP_HTTP_SERVER_H
#define VORTEX_SERVER_HTTP_HTTP_SERVER_H

#include <maze/object.h>
#include <Core/Cache/Redis.h>

namespace Vortex {
	namespace Server {
		namespace Http {
			class HttpServer {
			private:
				maze::object config_;
				Vortex::Core::Cache::Redis redis_;

			public:
				void start(maze::object config);
			};
		}  // namespace Http
	}  // namespace Server
}  // namespace Vortex

#endif  // VORTEX_SERVER_HTTP_HTTP_SERVER_H
