#include <Core/Cache/Cache.h>
#include <Core/Exception/CacheException.h>
#ifdef VORTEX_HAS_FEATURE_REDIS
#include <Core/Cache/Backends/RedisBackend.h>
#endif
#include <Core/Cache/Backends/MemoryCacheBackend.h>
#include <Core/Cache/Backends/DummyCacheBackend.h>

namespace Vortex {
    namespace Core {
        namespace Cache {
            Cache::Cache() {

            }

            void Cache::initialize(const Maze::Element& cache_config) {
                mtx_.lock();
                cache_config_ = cache_config;
                initialized_ = false;

                Backends::DummyCacheBackend* dummy_backend = static_cast<Backends::DummyCacheBackend*>(Backends::dummy_cache_exports.get_backend_instance());
                available_backends_.push_back(std::make_pair<std::string, ICacheBackend*>(
                    Backends::dummy_cache_exports.backend_name,
                    static_cast<ICacheBackend*>(dummy_backend)
                    ));
                default_backend_ = Backends::dummy_cache_exports.backend_name;

                if (cache_config.is_bool("enabled") && cache_config["enabled"].get_bool() == true) {
                    Backends::MemoryCacheBackend* memory_backend = static_cast<Backends::MemoryCacheBackend*>(Backends::memory_cache_exports.get_backend_instance());
                    memory_backend->set_config(cache_config.get("config").get("MemoryCache"));
                    available_backends_.push_back(std::make_pair<std::string, ICacheBackend*>(
                        Backends::memory_cache_exports.backend_name,
                        static_cast<ICacheBackend*>(memory_backend)
                        ));

                    if (memory_backend->is_enabled()) {
                        default_backend_ = Backends::memory_cache_exports.backend_name;
                    }


#ifdef VORTEX_HAS_FEATURE_REDIS
                    Backends::RedisBackend* redis_backend = static_cast<Backends::RedisBackend*>(Backends::redis_exports.get_backend_instance());
                    redis_backend->set_config(cache_config.get("config").get("Redis"));

                    if (redis_backend->is_enabled()) {
                        redis_backend->connect();

                        available_backends_.push_back(std::make_pair<std::string, ICacheBackend*>(
                            Backends::redis_exports.backend_name,
                            static_cast<ICacheBackend*>(redis_backend)
                            ));

                        default_backend_ = Backends::redis_exports.backend_name;
                    }
#endif
                }

                if (cache_config_.is_string("default_backend")) {
                    const std::string backend_name = cache_config["default_backend"].get_string();
                    bool backend_exists = false;

                    for (auto b : available_backends_) {
                        if (b.first == backend_name) {
                            default_backend_ = backend_name;
                            backend_exists = true;
                            break;
                        }
                    }

                    if (!backend_exists) {
                        throw Exception::CacheException("Cache backend " + backend_name + " set as default_backend in config is not available");
                    }
                }

                initialized_ = true;
                mtx_.unlock();
            }

            const bool Cache::is_initialized() const {
                return initialized_;
            }

            std::string Cache::get(const std::string& key) const {
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

            ICacheBackend* Cache::get_backend() const {
                return get_backend(default_backend_);
            }

            ICacheBackend* Cache::get_backend(const std::string& backend_name) const {
                if (!initialized_) {
                    throw Exception::CacheException("Cache backends are not initialized");
                }

                if (available_backends_.size() == 0) {
                    throw Exception::CacheException("No cache backends are available");
                }

                if (available_backends_[0].first == backend_name) {
                    return available_backends_[0].second;
                }

                for (int i = 1; i < this->available_backends_.size(); ++i) {
                    if (this->available_backends_[i].first == backend_name) {
                        return this->available_backends_[i].second;
                    }
                }

                throw Exception::CacheException("Cache backend '" + backend_name + "' is not available");
            }
        }  // namespace Cache
    }  // namespace Core
}  // namespace Vortex
