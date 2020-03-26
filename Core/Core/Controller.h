#ifndef VORTEX_CORE_FRAMEWORK_CONTROLLER_H
#define VORTEX_CORE_FRAMEWORK_CONTROLLER_H

#include <string>
#include <Maze/Object.hpp>
#include <Maze/Array.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class Controller {
		private:
			Framework* framework_;
			Maze::Object controller_;

		public:
			Controller(Framework* framework);

			void find(std::string app_id, std::string name, std::string method);

			std::string get_id();
			std::string get_name();
			Maze::Array get_app_ids();
			std::string get_script();
			std::string get_post_script();
			std::string get_content_type();
			std::string get_method();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_CONTROLLER_H
