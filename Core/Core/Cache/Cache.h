#ifndef VORTEX_CORE_CACHE_CACHE_H
#define VORTEX_CORE_CACHE_CACHE_H

#include <string>
#include <vector>
#include <mutex>
#include <Maze/Maze.hpp>
#include <Core/Cache/ICacheBackend.h>

namespace Vortex {
	namespace Core {
		namespace Cache {
			class Cache {
			private:
				std::vector<std::pair<std::string, ICacheBackend*>> available_backends_;
				std::string default_backend_;
				Maze::Element cache_config_;
				bool initialized_ = false;
				std::mutex mtx_;

			public:
				Cache();

				void initialize(const Maze::Element& cache_config);
				const bool is_initialized() const;

				std::string get(const std::string& key) const;
				void set(const std::string& key, const std::string& value, int expire_seconds = 180) const;
				bool exists(const std::string& key) const;
				void remove(const std::string& key) const;
				void set_expiry(const std::string& key, int seconds) const;

				ICacheBackend* get_backend() const;
				ICacheBackend* get_backend(const std::string& backend_name) const;
			};
		}  // namespace Cache
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_CACHE_CACHE_H
