#ifndef VORTEX_CORE_STORAGE_STORAGE_H
#define VORTEX_CORE_STORAGE_STORAGE_H

#include <string>
#include <maze/object.h>

namespace Vortex {
	namespace Core {
		class Framework;

		namespace Storage {
			class Storage {
			private:
				Framework* framework_;
				std::string backend_;

			public:
				Storage(Framework* framework);

				const std::string get_backend();
			};
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_STORAGE_H
