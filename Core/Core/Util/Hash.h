#ifndef VORTEX_CORE_UTIL_HASH_H
#define VORTEX_CORE_UTIL_HASH_H

#include <string>
#include <Core/DLLSupport.h>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace Hash {
				std::string VORTEX_CORE_API sha1(const std::string& value);
				std::string VORTEX_CORE_API sha1(const unsigned char* value, const size_t length);
				std::string VORTEX_CORE_API sha256(const std::string& value);
				std::string VORTEX_CORE_API sha256(const unsigned char* value, const size_t length);
				//std::string VORTEX_CORE_API sha512(const std::string& value);
				std::string VORTEX_CORE_API sha512(const unsigned char* value, const size_t length);
				//std::string VORTEX_CORE_API md5(const std::string& value);
				std::string VORTEX_CORE_API md5(const unsigned char* value, const size_t length);

				std::string VORTEX_CORE_API hex_encode(const unsigned char* value, const size_t length);
			}  // namespace Hash
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_UTIL_HASH_H
