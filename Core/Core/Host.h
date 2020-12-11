#ifndef VORTEX_CORE_FRAMEWORK_HOST_H
#define VORTEX_CORE_FRAMEWORK_HOST_H

#include <string>
#include <Maze/Maze.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class Host {
		private:
			Framework* framework_;
			Maze::Element host_;

		public:
			Host(Framework* framework);

			void find(const std::string& hostname);

			const std::string& get_id() const;
			const std::string& get_hostname() const;
			const std::string& get_app_id() const;
			const Maze::Element get_config() const;
			const std::string& get_script() const;
			const std::string& get_post_script() const;
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_HOST_H
