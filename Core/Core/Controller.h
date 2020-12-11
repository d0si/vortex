#ifndef VORTEX_CORE_FRAMEWORK_CONTROLLER_H
#define VORTEX_CORE_FRAMEWORK_CONTROLLER_H

#include <string>
#include <Maze/Maze.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class Controller {
		private:
			Framework* framework_;
			Maze::Element controller_;

		public:
			Controller(Framework* framework);

			void find(std::string app_id, std::string name, std::string method);

			const std::string& get_id() const;
			const std::string& get_name() const;
			const Maze::Element get_app_ids() const;
			const std::string& get_script() const;
			const std::string& get_post_script() const;
			const std::string& get_content_type() const;
			const std::string& get_method() const;
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_CONTROLLER_H
