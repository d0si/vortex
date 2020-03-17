#ifndef VORTEX_CORE_FRAMEWORK_VIEW_H
#define VORTEX_CORE_FRAMEWORK_VIEW_H

#include <string>
#include <Maze/Object.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class View {
		private:
			Framework* framework_;

			std::string rendered_;
			Maze::Object template_;
			Maze::Object page_;

		public:
			View(Framework* framework);

			void output();
			void respond();
			void echo(std::string contents);
			void set_content_type(std::string content_type);
			void set_status_code(int status_code);
			void clear();
			void finish();
			std::string parse(std::string code);

			void set_template(std::string name);
			std::string parse_template();

			void set_page(std::string name);
			std::string parse_page();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_VIEW_H
