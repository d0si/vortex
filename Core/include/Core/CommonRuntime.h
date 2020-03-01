#ifndef VORTEX_CORE_COMMONRUNTIME_H
#define VORTEX_CORE_COMMONRUNTIME_H

#include <Core/Storage/Storage.h>

namespace Vortex {
	namespace Core {
		class CommonRuntime {
		private:
			Core::Storage::Storage storage_;

		public:
			CommonRuntime();

			Core::Storage::Storage* get_storage();

		public:
			static CommonRuntime Instance;
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_COMMONRUNTIME_H
