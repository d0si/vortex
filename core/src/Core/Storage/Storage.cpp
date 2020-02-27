#include <Core/Storage/Storage.h>
#include <Core/Framework.h>
#include <Core/Storage/Filesystem/FilesystemBackend.h>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <Core/Storage/Mongo/MongoBackend.h>
#endif

namespace Vortex {
	namespace Core {
		namespace Storage {
			Storage::Storage(Framework* framework) : framework_(framework) {
				Filesystem::FilesystemBackend* fs_backend = static_cast<Core::Storage::Filesystem::FilesystemBackend*>(Core::Storage::Filesystem::exports.get_backend_instance());

				this->available_backends_.push_back(std::make_pair<std::string, Interface::IBackend*>(
					Core::Storage::Filesystem::exports.backend_name,
					static_cast<Core::Storage::Interface::IBackend*>(fs_backend)
					));

#ifdef VORTEX_HAS_FEATURE_MONGO
				Mongo::MongoBackend* mongo_backend = static_cast<Core::Storage::Mongo::MongoBackend*>(Core::Storage::Mongo::exports.get_backend_instance());
				mongo_backend->get_client()->set_config(framework_->config_["storage"].get_object()["mongo"].get_object());

				if (mongo_backend->get_client()->is_enabled()) {
					mongo_backend->get_client()->connect();

					this->available_backends_.push_back(std::make_pair<std::string, Interface::IBackend*>(
						Core::Storage::Mongo::exports.backend_name,
						static_cast<Core::Storage::Interface::IBackend*>(mongo_backend)
						));

					this->default_backend_ = Core::Storage::Mongo::exports.backend_name;
				} else {
					this->default_backend_ = Core::Storage::Filesystem::exports.backend_name;
				}
#else
				this->default_backend_ = Core::Storage::Filesystem::exports.backend_name;
#endif

				if (this->framework_->get_config().is_object("storage")) {
					maze::object storage_config = this->framework_->get_config()["storage"].get_object();

					if (storage_config.is_string("backend")) {
						const std::string backend_name = storage_config["backend"].get_string();
						bool backend_exists = false;

						for (auto b : this->available_backends_) {
							if (b.first == backend_name) {
								this->default_backend_ = backend_name;
								backend_exists = true;
								break;
							}
						}

						if (!backend_exists) {
							throw std::runtime_error("Storage backend " + backend_name + " is not available");
							// TODO: Throw more useful exception
						}
					}
				}
			}

			Interface::IBackend* Storage::get_backend() {
				return this->get_backend(this->default_backend_);
			}

			Interface::IBackend* Storage::get_backend(std::string backend_name) {
				if (this->available_backends_.size() == 0) {
					return nullptr;
				}

				if (this->available_backends_[0].first == backend_name) {
					return this->available_backends_[0].second;
				}

				for (int i = 1; i < this->available_backends_.size(); ++i) {
					if (this->available_backends_[i].first == backend_name) {
						return this->available_backends_[i].second;
					}
				}

				return nullptr;
			}
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
