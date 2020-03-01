#ifndef VORTEX_CORE_FRAMEWORK_APPLICATION_H
#define VORTEX_CORE_FRAMEWORK_APPLICATION_H

#include <string>
#include <Maze/Object.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class Application {
		private:
			Framework* framework_;
			Maze::Object application_;

		public:
			Application(Framework* framework);

			void find(std::string app_id);

			std::string get_id();
			std::string get_title();
			Maze::Object get_config();
			std::string get_script();
			std::string get_post_script();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
