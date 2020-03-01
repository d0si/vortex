#include <Core/Storage/Storage.h>
#include <Core/Framework.h>
#include <Core/Storage/Filesystem/FilesystemBackend.h>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <Core/Storage/Mongo/MongoBackend.h>
#endif

namespace Vortex {
	namespace Core {
		namespace Storage {
			Storage::Storage() {
				
			}

			void Storage::initialize(Maze::Object storage_config) {
				this->storage_config_ = storage_config;
				this->initialized_ = false;

				Filesystem::FilesystemBackend* fs_backend = static_cast<Core::Storage::Filesystem::FilesystemBackend*>(Core::Storage::Filesystem::exports.get_backend_instance());

				this->available_backends_.push_back(std::make_pair<std::string, Interface::IBackend*>(
					Core::Storage::Filesystem::exports.backend_name,
					static_cast<Core::Storage::Interface::IBackend*>(fs_backend)
					));

#ifdef VORTEX_HAS_FEATURE_MONGO
				Mongo::MongoBackend* mongo_backend = static_cast<Core::Storage::Mongo::MongoBackend*>(Core::Storage::Mongo::exports.get_backend_instance());
				mongo_backend->get_client()->set_config(this->storage_config_["config"].get_object()["Mongo"].get_object());

				if (mongo_backend->get_client()->is_enabled()) {
					mongo_backend->get_client()->connect();

					this->available_backends_.push_back(std::make_pair<std::string, Interface::IBackend*>(
						Core::Storage::Mongo::exports.backend_name,
						static_cast<Core::Storage::Interface::IBackend*>(mongo_backend)
						));

					this->default_backend_ = Core::Storage::Mongo::exports.backend_name;
				}
				else {
					this->default_backend_ = Core::Storage::Filesystem::exports.backend_name;
				}
#else
				this->default_backend_ = Core::Storage::Filesystem::exports.backend_name;
#endif

				if (this->storage_config_.is_string("default_backend")) {
					const std::string backend_name = storage_config["default_backend"].get_string();
					bool backend_exists = false;

					for (auto b : this->available_backends_) {
						if (b.first == backend_name) {
							this->default_backend_ = backend_name;
							backend_exists = true;
							break;
						}
					}

					if (!backend_exists) {
						throw std::runtime_error("Storage backend " + backend_name + " requested in config is not available");
						// TODO: Throw more useful exception
					}
				}

				this->initialized_ = true;
			}

			const bool Storage::is_initialized() const {
				return this->initialized_;
			}

			Interface::IBackend* Storage::get_backend() {
				return this->get_backend(this->default_backend_);
			}

			Interface::IBackend* Storage::get_backend(std::string backend_name) {
				if (!this->initialized_) {
					throw std::runtime_error("Storage instance is not initialized");
				}

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
