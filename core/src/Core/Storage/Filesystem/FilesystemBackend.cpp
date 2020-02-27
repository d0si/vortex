#include <Core/Storage/Filesystem/FilesystemBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Filesystem {
				FilesystemBackend::FilesystemBackend() {

				}

				FilesystemBackend::~FilesystemBackend() {

				}

				void FilesystemBackend::insert(std::string database, std::string collection, std::string value) {

				}

				std::string FilesystemBackend::find(std::string database, std::string collection, std::string query) {
					return "";
				}

				void FilesystemBackend::update(std::string database, std::string collection, std::string query, std::string new_value) {

				}

				void FilesystemBackend::remove(std::string database, std::string collection, std::string query) {

				}

				Storage::Interface::IBackend* get_backend() {
					static FilesystemBackend instance;
					return &instance;
				}
			}  // namespace Filesystem
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
