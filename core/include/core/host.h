#ifndef VORTEX_CORE_FRAMEWORK_HOST_H
#define VORTEX_CORE_FRAMEWORK_HOST_H

#include <string>
#include <maze/object.h>

namespace Vortex {
	namespace Core {
		class Framework;

		class Host {
		private:
			Framework* framework_;
			maze::object host_;

		public:
			Host(Framework* framework);

			void find(std::string hostname);

			std::string get_id();
			std::string get_hostname();
			std::string get_app_id();
			maze::object get_config();
			std::string get_script();
			std::string get_post_script();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_HOST_H
