#ifndef VORTEX_SERVER_HTTP_HTTP_SERVER_H
#define VORTEX_SERVER_HTTP_HTTP_SERVER_H

#include <maze/object.h>
#include <core/cache/redis.h>

namespace vortex {
	namespace server {
		namespace http {
			class HttpServer {
			private:
				maze::object config_;
				Vortex::Core::Cache::Redis redis_;

			public:
				void start(maze::object config);
			};
		}  // namespace http
	}  // namespace server
}  // namespace vortex

#endif  // VORTEX_SERVER_HTTP_HTTP_SERVER_H
