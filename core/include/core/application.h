#ifndef VORTEX_CORE_FRAMEWORK_APPLICATION_H
#define VORTEX_CORE_FRAMEWORK_APPLICATION_H

#include <string>
#include <maze/object.h>

namespace Vortex {
	namespace Core {
		class Framework;

		class Application {
		private:
			Framework* framework_;
			maze::object application_;

		public:
			Application(Framework* framework);

			void find(std::string app_id);

			std::string get_id();
			std::string get_title();
			maze::object get_config();
			std::string get_script();
			std::string get_post_script();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
