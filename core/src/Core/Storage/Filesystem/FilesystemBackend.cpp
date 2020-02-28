#include <Core/Storage/Filesystem/FilesystemBackend.h>
#include <maze/array.h>

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
					maze::array results;

					if (database == "vortex") {
						if (collection == "hosts") {
							maze::object host("hostname", "localhost");
							host.set("app_id", "0");
							host.set("script", "view.echo('Default host script.')");

							results.push(host);
						}
						else if (collection == "apps") {
							maze::object app("hostname", "localhost");
							app.set("title", "Default application");
							app.set("script", "view.echo('Default application script.')");

							results.push(app);
						}
						else if (collection == "controllers") {
							maze::object app("name", "index");
							app.set("app_ids", maze::array().push(0));
							app.set("script", "view.echo('Default controller script.')");

							results.push(app);
						}
					}

					return results.to_json();
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
