#ifndef VORTEX_CORE_FRAMEWORK_APPLICATION_H
#define VORTEX_CORE_FRAMEWORK_APPLICATION_H

#include <string>
#include <Maze/Maze.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class Application {
		private:
			Framework* framework_;
			Maze::Element application_;

		public:
			Application(Framework* framework);

			void find(const std::string& app_id);

			const std::string& get_id() const;
			const std::string& get_title() const;
			const Maze::Element get_config() const;
			const std::string& get_script() const;
			const std::string& get_post_script() const;

			Maze::Element find_object_in_application_storage(const std::string& collection, const Maze::Element& query, bool search_other_storages = true) const;
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
