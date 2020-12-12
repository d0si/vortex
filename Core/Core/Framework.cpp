#include <Core/Framework.h>

namespace Vortex::Core {

	Framework::Framework(
		const Maze::Element& config,
		std::string client_ip,
		boost::beast::http::request<boost::beast::http::string_body>* request,
		boost::beast::http::response<boost::beast::http::string_body>* response
	)
		: config_(config),
		client_ip_(client_ip),
		request_(request),
		response_(response),
		router_(this),
		host_(this),
		application_(this),
		controller_(this),
		view_(this),
		script_(this) {

	}

	void Framework::setup() {
		host_.find(router_.get_hostname());

		script_.setup();

		application_.find(host_.get_app_id());

		config_.apply(application_.get_config());
		config_.apply(host_.get_config());

		router_.setup();

		controller_.find(
			application_.get_id(),
			router_.get_controller(),
			request_->method_string().to_string());
	}

	void Framework::run() {
		script_.exec(application_.get_script());
		script_.exec(host_.get_script());
		script_.exec(controller_.get_script());

		script_.exec(application_.get_post_script());
		script_.exec(host_.get_post_script());
		script_.exec(controller_.get_post_script());

		view_.output();
		throw(0);
	}

	void Framework::exit() {
		view_.respond();

		throw(0);
	}

	const Maze::Element& Framework::get_config() const {
		return this->config_;
	}

}
