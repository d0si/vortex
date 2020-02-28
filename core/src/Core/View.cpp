#include <Core/View.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>

namespace Vortex {
	namespace Core {
		View::View(Framework* framework) : framework_(framework) {
		}

		void View::output() {
			rendered_ += parse_template();

			respond();
		}

		void View::respond() {
			framework_->response_->body() = rendered_;
		}

		void View::echo(std::string contents) {
			rendered_ += contents;
		}

		void View::clear() {
			framework_->response_->body() = "";
			rendered_.clear();
		}

		void View::finish() {
			template_.clear();
			page_.clear();
			respond();
		}

		std::string View::parse(std::string code) {
			std::string rendered;

			enum grabbing_stage {
				String, Script, Echo, Comment
			};

			std::string script_code;
			grabbing_stage stage = String;

			for (size_t i = 0; i < code.length(); ++i) {
				char current = code[i];

				if (stage == grabbing_stage::String) {
					if (current == '{') {
						char next = code[i + 1];

						if (next == '{') {
							stage = grabbing_stage::Script;
							script_code.clear();
							++i;
						}
						else if (next == '=') {
							stage = grabbing_stage::Echo;
							script_code.clear();
							++i;
						}
						else if (next == '#') {
							stage = grabbing_stage::Comment;
							script_code.clear();
							++i;
						}
						else if (next == '\\') {
							rendered += current;
							i++;
						}
						else {
							rendered += current;
						}
					}
					else {
						rendered += current;
					}
				}
				else if (stage == grabbing_stage::Script) {
					if (current == '}') {
						char next = code[i + 1];

						if (next == '}') {
							// TODO: Execute script

							script_code.clear();

							stage = grabbing_stage::String;
							++i;

							if (code[i + 2] == '\n') {
								++i;
							}
						}
						else if (next == '\\') {
							script_code += current;
							++i;
						}
						else {
							script_code += current;
						}
					}
					else {
						script_code += current;
					}
				}
				else if (stage == grabbing_stage::Echo) {
					if (current == '=') {
						char next = code[i + 1];

						if (next == '}') {
							// TODO: Get script result as string

							script_code.clear();

							stage = grabbing_stage::String;
							++i;

							if (code[i + 2] == '\n') {
								++i;
							}
						}
						else if (next == '\\') {
							script_code += current;
							++i;
						}
						else {
							script_code += current;
						}
					}
					else {
						script_code += current;
					}
				}
				else if (stage == grabbing_stage::Comment) {
					if (current == '#') {
						char next = code[i + 1];

						if (next == '}') {
							stage = grabbing_stage::String;
							++i;

							if (code[i + 2] == '\n') {
								++i;
							}
						}
						else if (next == '\\') {
							++i;
						}
					}
				}
			}

			return rendered;
		}

		void View::set_template(std::string name) {
			maze::object query("name", name);
			query.set("app_ids", framework_->application_.get_id());

			template_ = maze::array::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
				->find("vortex", "templates", query.to_json()))
				.get(0).get_object();
			/*template_ = framework_->mongo_.get_collection("templates")
				.find_one(query);*/

			if (template_.is_empty()) {
				query.set_null("app_ids");

				template_ = maze::array::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->find("vortex", "templates", query.to_json()))
					.get(0).get_object();
				/*template_ = framework_->mongo_.get_collection("templates")
					.find_one(query);*/
			}

			if (template_.is_empty()) {
				template_.set("contents", "Template " + name + " not found");
			}
		}

		std::string View::parse_template() {
			if (template_.is_string("contents")) {
				return parse(template_["contents"].get_string());
			}

			return "";
		}

		void View::set_page(std::string name) {
			maze::object query("name", name);
			query.set("app_ids", framework_->application_.get_id());

			page_ = maze::array::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
				->find("vortex", "pages", query.to_json()))
				.get(0).get_object();
			/*page_ = framework_->mongo_.get_collection("pages")
				.find_one(query);*/

			if (page_.is_empty()) {
				query.set_null("app_ids");

				page_ = maze::array::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->find("vortex", "apps", query.to_json()))
					.get(0).get_object();
				/*page_ = framework_->mongo_.get_collection("pages")
					.find_one(query);*/
			}

			if (page_.is_empty()) {
				page_.set("contents", "Page " + name + " not found");
			}
		}

		std::string View::parse_page() {
			if (template_.is_string("contents")) {
				return parse(template_["contents"].get_string());
			}

			return "";
		}
	}  // namespace Core
}  // namespace Vortex
