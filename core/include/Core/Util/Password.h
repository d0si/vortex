#ifndef VORTEX_CORE_UTIL_PASSWORD_H
#define VORTEX_CORE_UTIL_PASSWORD_H

#include <string>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace Password {
				std::string hash_password(std::string password);
				std::string hash_password(std::string password, std::string salt, unsigned int iterations = 100000);
				bool verify_password(std::string password, std::string hashed_password);
				std::string generate_salt();
			}  // namespace Password
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_UTIL_PASSWORD_H
