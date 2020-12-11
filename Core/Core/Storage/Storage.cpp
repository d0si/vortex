#include <Core/Storage/Storage.h>
#include <Core/Storage/Filesystem/FilesystemBackend.h>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <Core/Storage/Mongo/MongoBackend.h>
#endif

namespace Vortex::Core::Storage {

    void Storage::initialize(const Maze::Element& storage_config) {
        _mtx.lock();
        _storage_config = storage_config;
        _initialized = false;

        Filesystem::FilesystemBackend* fs_backend = static_cast<Core::Storage::Filesystem::FilesystemBackend*>(Core::Storage::Filesystem::filesystem_exports.get_backend_instance());
        fs_backend->set_config(storage_config.get("config").get("Filesystem"));

        _available_backends.push_back(std::make_pair<std::string, StorageBackendInterface*>(
            Core::Storage::Filesystem::filesystem_exports.backend_name,
            static_cast<Core::Storage::StorageBackendInterface*>(fs_backend)
            ));

#ifdef VORTEX_HAS_FEATURE_MONGO
                Mongo::MongoBackend* mongo_backend = static_cast<Core::Storage::Mongo::MongoBackend*>(Core::Storage::Mongo::mongo_exports.get_backend_instance());
                mongo_backend->get_client()->set_config(storage_config.get("config").get("Mongo"));

                if (mongo_backend->get_client()->is_enabled()) {
                    mongo_backend->get_client()->connect();

                    available_backends_.push_back(std::make_pair<std::string, StorageBackendInterface*>(
                        Core::Storage::Mongo::mongo_exports.backend_name,
                        static_cast<Core::Storage::StorageBackendInterface*>(mongo_backend)
                        ));

                    _default_backend = Core::Storage::Mongo::mongo_exports.backend_name;
                }
                else {
                    _default_backend = Core::Storage::Filesystem::filesystem_exports.backend_name;
                }
#else
                _default_backend = Core::Storage::Filesystem::filesystem_exports.backend_name;
#endif

                if (_storage_config.is_string("default_backend")) {
                    const std::string backend_name = storage_config["default_backend"].get_string();
                    bool backend_exists = false;

                    for (auto b : _available_backends) {
                        if (b.first == backend_name) {
                            _default_backend = backend_name;
                            backend_exists = true;
                            break;
                        }
                    }

                    if (!backend_exists) {
                        throw std::runtime_error("Storage backend " + backend_name + " requested in config is not available");
                        // TODO: Throw more useful exception
                    }
                }

        _initialized = true;
        _mtx.unlock();
    }

    const bool Storage::is_initialized() const {
        return _initialized;
    }

    StorageBackendInterface* Storage::get_backend() {
        return get_backend(_default_backend);
    }

    StorageBackendInterface* Storage::get_backend(const std::string& backend_name) {
        if (!_initialized) {
            throw std::runtime_error("Storage instance is not initialized");
        }

        if (_available_backends.size() == 0) {
            return nullptr;
        }

        if (_available_backends[0].first == backend_name) {
            return _available_backends[0].second;
        }

        for (int i = 1; i < _available_backends.size(); ++i) {
            if (_available_backends[i].first == backend_name) {
                return _available_backends[i].second;
            }
        }

        return nullptr;
    }

}
