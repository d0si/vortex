#pragma once

#ifdef HAS_FEATURE_CPPREDIS
#include <cpp_redis/cpp_redis>
#endif
#include <Core/Caching/Cache.h>
#include <Maze/Maze.hpp>

namespace Vortex::Core::Caching::Backends {

    class RedisBackend : public CacheBackendInterface {
    public:
        RedisBackend();
        RedisBackend(const Maze::Element& redis_config);
        ~RedisBackend();

        void connect();
        void set_config(const Maze::Element& redis_config);
        const bool is_enabled() const;

        virtual const std::string get(const std::string& key) override;
        virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180) override;
        virtual bool exists(const std::string& key) override;
        virtual void remove(const std::string& key) override;
        virtual void set_expiry(const std::string& key, int seconds) override;

    private:
#ifdef HAS_FEATURE_CPPREDIS
        cpp_redis::client _client;
#endif
        Maze::Element _redis_config;
        bool _enabled = false;
    };


    CacheBackendInterface* get_redis_backend();


    static const CacheBackendDetails redis_exports = {
        "RedisBackend",
        "Redis",
        get_redis_backend
    };

}  // namespace Vortex::Core::Caching::Backends
