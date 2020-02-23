#ifndef VORTEX_CORE_UTIL_HASH_H
#define VORTEX_CORE_UTIL_HASH_H

#include <string>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace Hash {
				std::string sha1(const std::string& value);
				std::string sha1(const unsigned char* value, const size_t length);
				std::string sha256(const std::string& value);
				std::string sha256(const unsigned char* value, const size_t length);
				std::string sha512(const std::string& value);
				std::string sha512(const unsigned char* value, const size_t length);
				std::string md5(const std::string& value);
				std::string md5(const unsigned char* value, const size_t length);

				std::string hex_encode(const unsigned char* value, const size_t length);
			}  // namespace Hash
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_UTIL_HASH_H
