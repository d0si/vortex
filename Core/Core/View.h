#ifndef VORTEX_CORE_FRAMEWORK_VIEW_H
#define VORTEX_CORE_FRAMEWORK_VIEW_H

#include <string>
#include <Maze/Maze.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class View {
		private:
			Framework* framework_;

			std::string rendered_;
			Maze::Element template_;
			Maze::Element page_;

		public:
			View(Framework* framework);

			void output();
			void respond();

			void echo(const std::string& contents);
			void set_content_type(const std::string& content_type);
			void set_status_code(int status_code);
			void set_cookie(const std::string& cookie_name, const std::string& value, const std::string& params = "");
			void set_cookie(const std::string& cookie_string);

			void clear();
			void finish();
			std::string parse(const std::string& code);

			void set_template(const std::string& name);
			std::string parse_template();

			void set_page(const std::string& name);
			std::string parse_page();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_VIEW_H
