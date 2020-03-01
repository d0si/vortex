#include <Core/CommonRuntime.h>

namespace Vortex {
	namespace Core {
		CommonRuntime::CommonRuntime() {

		}

		Core::Storage::Storage* CommonRuntime::get_storage() {
			return &this->storage_;
		}

		CommonRuntime CommonRuntime::Instance;
	}  // namespace Core
}  // namespace Vortex
