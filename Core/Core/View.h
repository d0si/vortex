#pragma once

#include <string>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core {

	class Framework;


	class View {
	public:
		VORTEX_CORE_API View(Framework* framework);

		VORTEX_CORE_API void output();
		VORTEX_CORE_API void respond();

		VORTEX_CORE_API void echo(const std::string& contents);
		VORTEX_CORE_API void set_content_type(const std::string& content_type);
		VORTEX_CORE_API void set_status_code(int status_code);
		VORTEX_CORE_API void set_cookie(const std::string& cookie_name, const std::string& value, const std::string& params = "");
		VORTEX_CORE_API void set_cookie(const std::string& cookie_string);

		VORTEX_CORE_API void clear();
		VORTEX_CORE_API void finish();
		VORTEX_CORE_API std::string parse(const std::string& code);

		VORTEX_CORE_API void set_template(const std::string& name);
		VORTEX_CORE_API std::string parse_template();

		VORTEX_CORE_API void set_page(const std::string& name);
		VORTEX_CORE_API std::string parse_page();

	private:
		Framework* _framework;

		std::string _rendered;
		Maze::Element _template;
		Maze::Element _page;
	};

}  // namespace Vortex::Core
