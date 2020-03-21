#ifndef VORTEX_CORE_CACHE_BACKENDS_REDISBACKEND_H
#define VORTEX_CORE_CACHE_BACKENDS_REDISBACKEND_H

#ifdef VORTEX_HAS_FEATURE_REDIS
#include <cpp_redis/cpp_redis>
#endif
#include <Core/Cache/ICacheBackend.h>
#include <Maze/Object.hpp>

namespace Vortex {
    namespace Core {
        namespace Cache {
            namespace Backends {
                class RedisBackend : public ICacheBackend {
                private:
#ifdef VORTEX_HAS_FEATURE_REDIS
                    cpp_redis::client client_;
#endif
                    Maze::Object redis_config_;
                    bool enabled = false;

                public:
                    RedisBackend();
                    RedisBackend(const Maze::Object& redis_config);
                    ~RedisBackend();

                    void connect();
                    void set_config(const Maze::Object& redis_config);
                    const bool is_enabled() const;

                    virtual std::string get(const std::string& key);
                    virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180);
                    virtual bool exists(const std::string& key);
                    virtual void remove(const std::string& key);
                    virtual void set_expiry(const std::string& key, int seconds);
                };

                Core::Cache::ICacheBackend* get_redis_backend();

                static const Core::Cache::CacheBackendDetails redis_exports = {
                    "RedisBackend",
                    "Redis",
                    get_redis_backend
                };
            }  // namespace Backends
        }  // namespace Cache
    }  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_CACHE_BACKENDS_REDISBACKEND_H
