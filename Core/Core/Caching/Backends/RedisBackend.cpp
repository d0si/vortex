#include <Core/Caching/Backends/RedisBackend.h>

namespace Vortex::Core::Caching::Backends {

    RedisBackend::RedisBackend() {}

    RedisBackend::RedisBackend(const Maze::Element& redis_config) {
        set_config(redis_config);
    }

    RedisBackend::~RedisBackend() {
#ifdef HAS_FEATURE_CPPREDIS
        if (_client.is_connected()) {
            _client.sync_commit();
            _client.disconnect();
        }
#endif
    }

    void RedisBackend::connect() {
#ifdef HAS_FEATURE_CPPREDIS
        if (_enabled) {
            std::string address = "127.0.0.1";
            int port = 6379;

            if (_redis_config.is_string("address")) {
                address = _redis_config["address"].get_string();
            }

            if (_redis_config.is_int("port")) {
                port = _redis_config["port"].get_int();
            }

            _client.connect(address, port);
        }
#endif
    }

    void RedisBackend::set_config(const Maze::Element& redis_config) {
        _redis_config = redis_config;

        if (_redis_config.is_bool("enabled")) {
            _enabled = _redis_config["enabled"].get_bool();
        }
    }

    const bool RedisBackend::is_enabled() const {
        return _enabled;
    }

    const std::string RedisBackend::get(const std::string& key) {
#ifdef HAS_FEATURE_CPPREDIS
        if (_enabled && _client.is_connected()) {
            std::future<cpp_redis::reply> reply = _client.get(key);
            _client.sync_commit();
            reply.wait();

            return reply.get().as_string();
        }
        else {
            return "";
        }
#else
        return "";
#endif
    }

    void RedisBackend::set(const std::string& key, const std::string& value, int expire_seconds) {
#ifdef HAS_FEATURE_CPPREDIS
        if (_enabled && _client.is_connected()) {
            _client.set(key, value);

            _client.sync_commit();

            if (expire_seconds > 0) {
                set_expiry(key, expire_seconds);
            }
        }
#endif
    }

    bool RedisBackend::exists(const std::string& key) {
#ifdef HAS_FEATURE_CPPREDIS
        if (_enabled && _client.is_connected()) {
            std::vector<std::string> keys;
            keys.push_back(key);

            std::future<cpp_redis::reply> reply = _client.exists(keys);
            _client.sync_commit();
            reply.wait();

            return reply.get().as_integer() == 1;
        }
        else {
            return false;
        }
#else
        return false;
#endif
    }

    void RedisBackend::remove(const std::string& key) {
#ifdef HAS_FEATURE_CPPREDIS
        if (_enabled && _client.is_connected()) {
            std::vector<std::string> keys;
            keys.push_back(key);

            _client.del(keys);
            _client.sync_commit();
        }
#endif
    }

    void RedisBackend::set_expiry(const std::string& key, int seconds) {
#ifdef HAS_FEATURE_CPPREDIS
        if (_enabled && _client.is_connected()) {
            _client.expire(key, seconds);
            _client.sync_commit();
        }
#endif
    }

    CacheBackendInterface* get_redis_backend() {
        static RedisBackend instance;
        return &instance;
    }

}  // namespace Vortex::Core::Cache::Backends
