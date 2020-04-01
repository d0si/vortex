#include <Core/User.h>
#include <Core/Framework.h>
#include <Core/CommonRuntime.h>
#include <Core/Util/Password.h>
#include <Core/Util/Random.h>

namespace Vortex {
	namespace Core {
		User::User(Framework* framework) : framework_(framework) {

		}

		void User::setup() {
			Maze::Object user_config = framework_->get_config()["user"].get_object();
			search_other_storages_ = (user_config.is_bool("search_master_db") && user_config["search_master_db"].get_bool() == true);

			if (user_config.is_object("session")) {
				Maze::Object session_config = user_config["session"].get_object();

				if (session_config.is_string("cookie_name")) {
					session_cookie_name_ = session_config["cookie_name"].get_string();
				}
			}

			bool session_cookie_exists = false;
			std::string session_cookie_value = framework_->router_.get_cookie(session_cookie_name_, &session_cookie_exists);

			if (!session_cookie_exists || session_cookie_value.length() == 0) {
				return;
			}

			Maze::Object session_query("session_id", session_cookie_value);
			Maze::Object session_value = framework_->application_.find_object_in_application_storage("sessions", session_cookie_value, false);

			if (session_value.is_empty() || !session_value.is_string("user_id") ||
				!session_value.is_bool("valid") || session_value["valid"].get_bool() == false) {
				remove_session_cookie();

				return;
			}

			std::string user_id = session_value["user_id"].get_string();
			Maze::Object user_query;
			user_query.set("_id", Maze::Object("$oid", user_id));
			Maze::Object user_value = framework_->application_.find_object_in_application_storage("users", user_query, search_other_storages_);

			if (user_value.is_empty()) {
				remove_session_cookie();

				return;
			}

			session_ = session_value;
			user_ = user_value;
			logged_in_ = true;
		}

		void User::remove_session_cookie() {
			bool session_cookie_exists = false;
			std::string session_cookie_value = framework_->router_.get_cookie(session_cookie_name_, &session_cookie_exists);

			if (session_cookie_exists) {
				framework_->view_.set_cookie(session_cookie_name_ + "=null;Expires=Thu, 01 Jan 1970 00:00:00;Path=/");
			}
		}

		void User::logout() {
			remove_session_cookie();

			if (!session_.is_empty()) {
				std::string database;
				Maze::Object result;
				Maze::Object query = Maze::Object("session_id", session_["session_id"].get_string());

				if (framework_->get_config()["application"].get_object().is_string("database")) {
					database = framework_->get_config()["application"].get_object()["database"].get_string();
				}
				else {
					database = framework_->application_.get_id();
				}

				result = Maze::Object::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->simple_find_first(database, "sessions", query.to_json()));

				if (!result.is_empty()) {
					result.set("valid", false);

					Core::CommonRuntime::Instance.get_storage()->get_backend()
						->simple_replace_first(database, "sessions", query.to_json(), result.to_json());
				}

				session_.clear();
				user_.clear();

				framework_->view_.send_refresh();
			}
		}

		bool User::login(std::string username, std::string password) {
			Maze::Object user_value = framework_->application_.find_object_in_application_storage("users", Maze::Object("username", username), search_other_storages_);

			if (user_value.is_empty()) {
				return false;
			}

			if (!user_value.is_object("password") || !user_value["password"].get_object().is_string("hash")) {
				return false;
			}

			Maze::Object password_obj = user_value["password"].get_object();
			
			std::string hashed_password = password_obj["hash"].get_string();
			if (!Util::Password::verify_password(password, hashed_password)) {
				return false;
			}

			Maze::Object session_obj("user_id", user_value["_id"].get_object()["$oid"].get_string());
			session_obj.set("session_id", Util::Random::random_string(24));

			std::string database;
			if (framework_->get_config()["application"].get_object().is_string("database")) {
				database = framework_->get_config()["application"].get_object()["database"].get_string();
			}
			else {
				database = framework_->application_.get_id();
			}

			Core::CommonRuntime::Instance.get_storage()->get_backend()
				->simple_insert(database, "sessions", session_obj.to_json());
			
			framework_->view_.set_cookie(session_cookie_name_ + "=" + session_obj["session_id"].get_string() + ";Expires=Wed, 01 Apr 2020 00:00:00 GMT;Path=/");

			return true;
		}

		std::string User::get_user_id() const {
			return user_["user_id"].get_string();
		}

		std::string User::get_username() const {
			return user_["username"].get_string();
		}

		bool User::is_logged_in() const {
			return logged_in_;
		}
	}  // namespace Core
}  // namespace Vortex
