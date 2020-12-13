#pragma once

#include <Core/Interfaces.h>

namespace Vortex::VortexFramework {

	class View : public Core::ViewInterface {
	public:
		VORTEX_CORE_API View(Core::FrameworkInterface* framework);
		VORTEX_CORE_API virtual ~View() override = default;

		VORTEX_CORE_API virtual void output() override;
		VORTEX_CORE_API virtual void respond() override;

		VORTEX_CORE_API virtual void echo(const std::string& contents) override;
		VORTEX_CORE_API virtual void set_content_type(const std::string& content_type) override;
		VORTEX_CORE_API virtual void set_status_code(int status_code) override;
		VORTEX_CORE_API virtual void set_cookie(const std::string& cookie_name, const std::string& value, const std::string& params = "") override;
		VORTEX_CORE_API virtual void set_cookie(const std::string& cookie_string) override;

		VORTEX_CORE_API virtual void clear() override;
		VORTEX_CORE_API virtual void finish() override;
		VORTEX_CORE_API virtual std::string parse(const std::string& code) override;

		VORTEX_CORE_API virtual void set_template(const std::string& name) override;
		VORTEX_CORE_API virtual std::string parse_template() override;

		VORTEX_CORE_API virtual void set_page(const std::string& name) override;
		VORTEX_CORE_API virtual std::string parse_page() override;

	protected:
		std::string _rendered;
		Maze::Element _template;
		Maze::Element _page;
	};

}  // namespace Vortex::VortexFramework
