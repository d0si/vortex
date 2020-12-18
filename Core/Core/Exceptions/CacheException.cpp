#include <Core/Exceptions/CacheException.hpp>

namespace Vortex::Core::Exceptions {

	CacheException::CacheException(const std::string& message)
		: VortexException(message, "") {}

	CacheException::CacheException(const std::string& message, const std::string& details)
		: VortexException(message, details, "Cache") {}

}
