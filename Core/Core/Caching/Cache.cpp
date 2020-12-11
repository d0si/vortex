#include <Core/Caching/Cache.h>
#include <sstream>
#include <Core/Exceptions/CacheException.h>
#ifdef HAS_FEATURE_CPPREDIS
#include <Core/Caching/Backends/RedisBackend.h>
#endif
#include <Core/Caching/Backends/MemoryCacheBackend.h>
#include <Core/Caching/Backends/DummyCacheBackend.h>

namespace Vortex::Core::Caching {

    void Cache::initialize(const Maze::Element& cache_config) {
        _mtx.lock();
        _cache_config = cache_config;
        _initialized = false;

        Backends::DummyCacheBackend* dummy_backend = static_cast<Backends::DummyCacheBackend*>(Backends::dummy_cache_exports.get_backend_instance());
        _available_backends.push_back(std::make_pair<std::string, CacheBackendInterface*>(
            Backends::dummy_cache_exports.backend_name,
            static_cast<CacheBackendInterface*>(dummy_backend)
            ));
        _default_backend = Backends::dummy_cache_exports.backend_name;

        if (cache_config.is_bool("enabled") && cache_config["enabled"].get_bool() == true) {
            Backends::MemoryCacheBackend* memory_backend = static_cast<Backends::MemoryCacheBackend*>(Backends::memory_cache_exports.get_backend_instance());
            memory_backend->set_config(cache_config.get("config").get("MemoryCache"));
            _available_backends.push_back(std::make_pair<std::string, CacheBackendInterface*>(
                Backends::memory_cache_exports.backend_name,
                static_cast<CacheBackendInterface*>(memory_backend)
                ));

            if (memory_backend->is_enabled()) {
                _default_backend = Backends::memory_cache_exports.backend_name;
            }

#ifdef HAS_FEATURE_CPPREDIS
            Backends::RedisBackend* redis_backend = static_cast<Backends::RedisBackend*>(Backends::redis_exports.get_backend_instance());
            redis_backend->set_config(cache_config.get("config").get("Redis"));

            if (redis_backend->is_enabled()) {
                redis_backend->connect();

                _available_backends.push_back(std::make_pair<std::string, CacheBackendInterface*>(
                    Backends::redis_exports.backend_name,
                    static_cast<CacheBackendInterface*>(redis_backend)
                    ));

                _default_backend = Backends::redis_exports.backend_name;
            }
#endif
        }

        if (_cache_config.is_string("default_backend")) {
            const std::string backend_name = cache_config["default_backend"].get_string();
            bool backend_exists = false;

            for (auto& b : _available_backends) {
                if (b.first == backend_name) {
                    _default_backend = backend_name;
                    backend_exists = true;
                    break;
                }
            }

            if (!backend_exists) {
                throw Exceptions::CacheException(
                    "Default backend unavailable",
                    (std::stringstream()
                        << "Cache backend '"
                        << backend_name
                        << "' set as default_backend is not available").str().c_str());
            }
        }

        _initialized = true;
        _mtx.unlock();
    }

    const bool Cache::is_initialized() const {
        return _initialized;
    }

    inline const std::string Cache::get(const std::string& key) const {
        return get_backend()->get(key);
    }

    void Cache::set(const std::string& key, const std::string& value, int expire_seconds) const {
        get_backend()->set(key, value, expire_seconds);
    }

    bool Cache::exists(const std::string& key) const {
        return get_backend()->exists(key);
    }

    void Cache::remove(const std::string& key) const {
        get_backend()->remove(key);
    }

    void Cache::set_expiry(const std::string& key, int seconds) const {
        get_backend()->set_expiry(key, seconds);
    }

    CacheBackendInterface* Cache::get_backend() const {
        return get_backend(_default_backend);
    }

    CacheBackendInterface* Cache::get_backend(const std::string& backend_name) const {
        if (!_initialized) {
            throw Exceptions::CacheException("Cache backends are not initialized");
        }

        if (_available_backends.size() == 0) {
            throw Exceptions::CacheException("No cache backends are available");
        }

        if (_available_backends[0].first == backend_name) {
            return _available_backends[0].second;
        }

        for (int i = 1; i < _available_backends.size(); ++i) {
            if (_available_backends[i].first == backend_name) {
                return _available_backends[i].second;
            }
        }

        throw Exceptions::CacheException(
            "Backend unavailable",
            (std::stringstream()
                << "Cache backend '"
                << backend_name
                << "' is not available").str().c_str());
    }

}
