#include <Core/Caching/Backends/MemoryCacheBackend.h>
#include <chrono>

namespace Vortex::Core::Caching::Backends {

    MemoryCacheBackend::MemoryCacheBackend() {}

    MemoryCacheBackend::MemoryCacheBackend(const Maze::Element& cache_config) {
        set_config(cache_config);
    }

    MemoryCacheBackend::~MemoryCacheBackend() {}

    void MemoryCacheBackend::set_config(const Maze::Element& cache_config) {
        _cache_config = cache_config;

        if (_cache_config.is_bool("enabled")) {
            _enabled = _cache_config["enabled"].get_bool();
        }
    }

    const bool MemoryCacheBackend::is_enabled() const {
        return _enabled;
    }

    const std::string MemoryCacheBackend::get(const std::string& key) {
        if (_enabled) {
            auto it = _cache_map.find(key);
            if (it != _cache_map.end()) {
                long long expiry_timestamp = it->second->second.expiry_timestamp;
                if (expiry_timestamp == 0 ||
                    get_current_time_millis() - expiry_timestamp < 100) {
                    return it->second->second.value;
                }
                else {
                    remove(key);
                }
            }
        }

        return "";
    }

    void MemoryCacheBackend::set(const std::string& key, const std::string& value, int expire_seconds) {
        if (_enabled) {
            remove(key);

            long long expires_at = expire_seconds > 0 ? get_current_time_millis() + (expire_seconds * (long long)60) * 1000 : 0;
            MemoryCacheEntry entry{
                expires_at,
                value
            };

            _cache_list.push_front(std::make_pair(key, entry));
            _cache_map[key] = _cache_list.begin();
        }
    }

    bool MemoryCacheBackend::exists(const std::string& key) {
        if (_enabled) {
            auto& it = _cache_map.find(key);
            if (it != _cache_map.end()) {
                if (it->second->second.expiry_timestamp == 0 ||
                    get_current_time_millis() - it->second->second.expiry_timestamp < 0) {
                    return true;
                }
                else {
                    remove(key);
                }
            }
        }

        return false;
    }

    void MemoryCacheBackend::remove(const std::string& key) {
        if (_enabled) {
            auto& it = _cache_map.find(key);
            if (it != _cache_map.end()) {
                _cache_list.erase(it->second);
                _cache_map.erase(key);
            }
        }
    }

    void MemoryCacheBackend::set_expiry(const std::string& key, int seconds) {
        if (_enabled) {
            auto& it = _cache_map.find(key);
            if (it != _cache_map.end()) {
                if (it->second->second.expiry_timestamp == 0 ||
                    get_current_time_millis() - it->second->second.expiry_timestamp < 0) {
                    it->second->second.expiry_timestamp =
                        seconds != 0 ? get_current_time_millis() + (seconds * (long long)60) * 1000 : 0;
                }
                else {
                    remove(key);
                }
            }
        }
    }

    long long MemoryCacheBackend::get_current_time_millis() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
    }

    CacheBackendInterface* get_memory_cache_backend() {
        static MemoryCacheBackend instance;
        return &instance;
    }

}
