#ifndef VORTEX_CORE_STORAGE_STORAGE_H
#define VORTEX_CORE_STORAGE_STORAGE_H

#include <string>
#include <vector>
#include <Core/Storage/Interface/IBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			class Storage {
			private:
				std::vector<std::pair<std::string, Interface::IBackend*>> available_backends_;
				std::string default_backend_;
				maze::object storage_config_;
				bool initialized_ = false;

			public:
				Storage();

				void initialize(maze::object storage_config);
				const bool is_initialized() const;

				Interface::IBackend* get_backend();
				Interface::IBackend* get_backend(std::string backend_name);
			};
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_STORAGE_H
