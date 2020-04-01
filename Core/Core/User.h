#ifndef VORTEX_CORE_FRAMEWORK_USER_H
#define VORTEX_CORE_FRAMEWORK_USER_H

#include <string>
#include <Maze/Object.hpp>

namespace Vortex {
	namespace Core {
		class Framework;

		class User {
		private:
			Framework* framework_;
			std::string session_cookie_name_ = "v_session";
			bool search_other_storages_;
			Maze::Object user_;
			Maze::Object session_;
			bool logged_in_ = false;

		public:
			User(Framework* framework);

			void setup();
			void remove_session_cookie();
			void logout();
			bool login(std::string username, std::string password);

			std::string get_user_id() const;
			std::string get_username() const;
			bool is_logged_in() const;
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_USER_H
