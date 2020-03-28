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

			void find(const std::string& app_id);

			std::string get_id() const;
			std::string get_title() const;
			Maze::Object get_config() const;
			std::string get_script() const;
			std::string get_post_script() const;

			Maze::Object find_object_in_application_storage(const std::string& collection, const Maze::Object& query, bool search_other_storages = true) const;
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
