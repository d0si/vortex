#ifndef VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H
#define VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H

#include <Core/Storage/Interface/IBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Filesystem {
				class FilesystemBackend: public Core::Storage::Interface::IBackend {
				public:
					FilesystemBackend();
					~FilesystemBackend();

					virtual void insert(std::string database, std::string collection, std::string value);
					virtual std::string find(std::string database, std::string collection, std::string query);
					virtual void update(std::string database, std::string collection, std::string query, std::string new_value);
					virtual void remove(std::string database, std::string collection, std::string query);
				};

				Core::Storage::Interface::IBackend* get_backend();

				static const Core::Storage::Interface::BackendDetails exports = {
					"FilesystemBackend",
					"Filesystem",
					get_backend
				};
			}  // namespace Filesystem
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H
