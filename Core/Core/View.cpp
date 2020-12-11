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

		void View::echo(const std::string& contents) {
			rendered_ += contents;
		}

		void View::set_content_type(const std::string& content_type) {
			framework_->response_->set(boost::beast::http::field::content_type, content_type);
		}

		void View::set_status_code(int status_code) {
			framework_->response_->result(boost::beast::http::int_to_status(status_code));
		}

		void View::set_cookie(const std::string& cookie_name, const std::string& value, const std::string& params) {
			set_cookie(cookie_name + '=' + value + ";" + (params.length() > 0 ? params + ";" : ""));
		}

		void View::set_cookie(const std::string& cookie_string) {
			framework_->response_->insert(boost::beast::http::field::set_cookie, cookie_string);
		}

		void View::clear() {
			framework_->response_->body() = "";
			rendered_.clear();
		}

		void View::finish() {
			template_.remove_all_children();
			page_.remove_all_children();
			respond();
		}

		std::string View::parse(const std::string& code) {
			const std::string old_rendered = rendered_;
			rendered_.clear();

			enum class grabbing_stage {
				String, Script, Echo, Comment
			};

			std::string script_code;
			grabbing_stage stage = grabbing_stage::String;

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
							rendered_ += current;
							i++;
						}
						else {
							rendered_ += current;
						}
					}
					else {
						rendered_ += current;
					}
				}
				else if (stage == grabbing_stage::Script) {
					if (current == '}') {
						char next = code[i + 1];

						if (next == '}') {
							framework_->script_.exec(script_code);

							script_code.clear();

							stage = grabbing_stage::String;
							++i;

							/*if (code[i + 2] == '\n') {
								++i;
							}*/
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
							framework_->script_.exec("var results = (" + script_code + "); if (results != undefined) { view.echo(results); }");

							script_code.clear();

							stage = grabbing_stage::String;
							++i;

							/*if (code[i + 2] == '\n') {
								++i;
							}*/
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

							/*if (code[i + 2] == '\n') {
								++i;
							}*/
						}
						else if (next == '\\') {
							++i;
						}
					}
				}
			}

			std::string new_rendered = rendered_;
			rendered_ = old_rendered;
			return new_rendered;
		}

		void View::set_template(const std::string& name) {
			template_.remove_all_children();

			std::string cache_key = "vortex.core.template.value." + framework_->application_.get_id() + "." + name;
			if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
				template_ = Maze::Element::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
			}

			if (!template_.has_children()) {
				Maze::Element query(
					{ "name", "app_id" },
					{ name, framework_->application_.get_id() }
				);
				
				template_ = framework_->application_.find_object_in_application_storage("templates", query);

				if (!template_.has_children()) {
					query["app_id"].set_as_null();
					
					template_ = framework_->application_.find_object_in_application_storage("templates", query);
				}

				if (template_.has_children()) {
					CommonRuntime::Instance.get_cache()->set(cache_key, template_.to_json(0));
				}
			}

			if (!template_.has_children()) {
				framework_->view_.echo("Template " + name + " not found");
				framework_->exit();
			}
		}

		std::string View::parse_template() {
			if (template_.is_string("contents")) {
				return parse(template_["contents"].get_string());
			}

			return "";
		}

		void View::set_page(const std::string& name) {
			page_.remove_all_children();

			std::string cache_key = "vortex.core.page.value." + framework_->application_.get_id() + "." + name;
			if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
				page_ = Maze::Element::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
			}

			if (!page_.has_children()) {
				Maze::Element query(
					{ "name", "app_id" },
					{ name, framework_->application_.get_id() }
				);

				page_ = framework_->application_.find_object_in_application_storage("pages", query);

				if (!page_.has_children()) {
					query["app_id"].set_as_null();
					
					page_ = framework_->application_.find_object_in_application_storage("pages", query);
				}

				if (page_.has_children()) {
					CommonRuntime::Instance.get_cache()->set(cache_key, page_.to_json(0));
				}
			}

			if (!page_.has_children()) {
				page_.set("contents", "Page " + name + " not found");
			}
		}
		
		std::string View::parse_page() {
			if (page_.is_string("contents")) {
				return parse(page_["contents"].get_string());
			}

			return "";
		}
	}  // namespace Core
}  // namespace Vortex
