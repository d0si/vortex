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

			void Storage::initialize(const Maze::Object& storage_config) {
				mtx_.lock();
				storage_config_ = storage_config;
				initialized_ = false;

				Filesystem::FilesystemBackend* fs_backend = static_cast<Core::Storage::Filesystem::FilesystemBackend*>(Core::Storage::Filesystem::filesystem_exports.get_backend_instance());
				fs_backend->set_config(storage_config_["config"].get_object()["Filesystem"].get_object());

				available_backends_.push_back(std::make_pair<std::string, IStorageBackend*>(
					Core::Storage::Filesystem::filesystem_exports.backend_name,
					static_cast<Core::Storage::IStorageBackend*>(fs_backend)
					));

#ifdef VORTEX_HAS_FEATURE_MONGO
				Mongo::MongoBackend* mongo_backend = static_cast<Core::Storage::Mongo::MongoBackend*>(Core::Storage::Mongo::mongo_exports.get_backend_instance());
				mongo_backend->get_client()->set_config(storage_config_["config"].get_object()["Mongo"].get_object());

				if (mongo_backend->get_client()->is_enabled()) {
					mongo_backend->get_client()->connect();

					available_backends_.push_back(std::make_pair<std::string, IStorageBackend*>(
						Core::Storage::Mongo::mongo_exports.backend_name,
						static_cast<Core::Storage::IStorageBackend*>(mongo_backend)
						));

					default_backend_ = Core::Storage::Mongo::mongo_exports.backend_name;
				}
				else {
					default_backend_ = Core::Storage::Filesystem::filesystem_exports.backend_name;
				}
#else
				default_backend_ = Core::Storage::Filesystem::filesystem_exports.backend_name;
#endif

				if (storage_config_.is_string("default_backend")) {
					const std::string backend_name = storage_config["default_backend"].get_string();
					bool backend_exists = false;

					for (auto b : available_backends_) {
						if (b.first == backend_name) {
							default_backend_ = backend_name;
							backend_exists = true;
							break;
						}
					}

					if (!backend_exists) {
						throw std::runtime_error("Storage backend " + backend_name + " requested in config is not available");
						// TODO: Throw more useful exception
					}
				}

				initialized_ = true;
				mtx_.unlock();
			}

			const bool Storage::is_initialized() const {
				return initialized_;
			}

			IStorageBackend* Storage::get_backend() {
				return get_backend(default_backend_);
			}

			IStorageBackend* Storage::get_backend(const std::string& backend_name) {
				if (!initialized_) {
					throw std::runtime_error("Storage instance is not initialized");
				}

				if (available_backends_.size() == 0) {
					return nullptr;
				}

				if (available_backends_[0].first == backend_name) {
					return available_backends_[0].second;
				}

				for (int i = 1; i < available_backends_.size(); ++i) {
					if (available_backends_[i].first == backend_name) {
						return available_backends_[i].second;
					}
				}

				return nullptr;
			}
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
