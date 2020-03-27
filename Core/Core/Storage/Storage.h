#ifndef VORTEX_CORE_STORAGE_STORAGE_H
#define VORTEX_CORE_STORAGE_STORAGE_H

#include <string>
#include <vector>
#include <Core/Storage/IStorageBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			class Storage {
			private:
				std::vector<std::pair<std::string, IStorageBackend*>> available_backends_;
				std::string default_backend_;
				Maze::Object storage_config_;
				bool initialized_ = false;

			public:
				Storage();

				void initialize(Maze::Object storage_config);
				const bool is_initialized() const;

				IStorageBackend* get_backend();
				IStorageBackend* get_backend(std::string backend_name);
			};
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_STORAGE_H
