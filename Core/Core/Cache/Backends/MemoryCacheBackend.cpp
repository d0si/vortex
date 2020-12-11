#include <Core/Cache/Backends/MemoryCacheBackend.h>
#include <chrono>

namespace Vortex {
    namespace Core {
        namespace Cache {
            namespace Backends {
                MemoryCacheBackend::MemoryCacheBackend() {

                }

                MemoryCacheBackend::MemoryCacheBackend(const Maze::Element& cache_config) {
                    set_config(cache_config);
                }

                MemoryCacheBackend::~MemoryCacheBackend() {

                }

                void MemoryCacheBackend::set_config(const Maze::Element& cache_config) {
                    cache_config_ = cache_config;

                    if (cache_config_.is_bool("enabled")) {
                        enabled_ = cache_config_["enabled"].get_bool();
                    }
                }

                const bool MemoryCacheBackend::is_enabled() const {
                    return enabled_;
                }

                std::string MemoryCacheBackend::get(const std::string& key) {
                    if (enabled_) {
                        auto it = cache_map_.find(key);
                        if (it != cache_map_.end()) {
                            if (it->second->second.expiry_timestamp == 0 ||
                                get_current_time_millis() - it->second->second.expiry_timestamp < 100) {
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
                    if (enabled_) {
                        remove(key);

                        MemoryCacheEntry entry{
                            expire_seconds != 0 ? get_current_time_millis() + (expire_seconds * 60) : 0,
                            value
                        };

                        cache_list_.push_front(std::make_pair(key, entry));
                        cache_map_[key] = cache_list_.begin();
                    }
                }

                bool MemoryCacheBackend::exists(const std::string& key) {
                    if (enabled_) {
                        auto it = cache_map_.find(key);
                        if (it != cache_map_.end()) {
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
                    if (enabled_) {
                        auto it = cache_map_.find(key);
                        if (it != cache_map_.end()) {
                            cache_list_.erase(it->second);
                            cache_map_.erase(key);
                        }
                    }
                }

                void MemoryCacheBackend::set_expiry(const std::string& key, int seconds) {
                    if (enabled_) {
                        auto it = cache_map_.find(key);
                        if (it != cache_map_.end()) {
                            if (it->second->second.expiry_timestamp == 0 ||
                                get_current_time_millis() - it->second->second.expiry_timestamp < 0) {
                                it->second->second.expiry_timestamp =
                                    seconds != 0 ? get_current_time_millis() + (seconds * 60) : 0;
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

                Core::Cache::ICacheBackend* get_memory_cache_backend() {
                    static MemoryCacheBackend instance;
                    return &instance;
                }
            }  // namespace Redis
        }  // namespace Cache
    }  // namespace Core
}  // namespace Vortex
