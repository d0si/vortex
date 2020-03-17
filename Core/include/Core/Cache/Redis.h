#ifndef VORTEX_CORE_CACHE_REDIS_H
#define VORTEX_CORE_CACHE_REDIS_H

#ifdef VORTEX_HAS_FEATURE_REDIS
#include <cpp_redis/cpp_redis>
#endif
#include <Maze/Object.hpp>

namespace Vortex {
	namespace Core {
		namespace Cache {
			class Redis {
			private:
#ifdef VORTEX_HAS_FEATURE_REDIS
				cpp_redis::client client_;
#endif
				Maze::Object redis_config_;
				bool enabled = true;

			public:
				Redis();
				Redis(const Maze::Object& redis_config);
				~Redis();

				void connect();
				void set_config(const Maze::Object& redis_config);
				std::string get(std::string key);
				void set(std::string key, std::string value, int expire_seconds = 180);
				bool exists(std::string key);
				void del(std::string key);
				void expire(std::string key, int seconds);
			};
		}  // namespace Cache
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_CACHE_REDIS_H
