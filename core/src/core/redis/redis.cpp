#include <core/redis/redis.h>

namespace vortex {
namespace core {
namespace redis {

Redis::Redis() {

}

Redis::Redis(const maze::object& redis_config) {
  set_config(redis_config);
}

Redis::~Redis() {
#ifdef VORTEX_HAS_FEATURE_REDIS
  if (client_.is_connected()) {
    client_.sync_commit();
    client_.disconnect();
  }
#endif
}

void Redis::connect() {
#ifdef VORTEX_HAS_FEATURE_REDIS
  if (enabled) {
    std::string address = "127.0.0.1";
    int port = 6379;

    if (redis_config_.is_string("address")) {
      address = redis_config_["address"].get_string();
    }

    if (redis_config_.is_string("port")) {
      port = redis_config_["port"].get_int();
    }

    client_.connect(address, port);
  }
#endif
}

void Redis::set_config(const maze::object& redis_config) {
  redis_config_ = redis_config;

  if (redis_config_.is_bool("enabled")) {
    enabled = redis_config_["enabled"].get_bool();
  }
}

std::string Redis::get(std::string key) {
#ifdef VORTEX_HAS_FEATURE_REDIS
  if (enabled && client_.is_connected()) {
    std::future<cpp_redis::reply> reply = client_.get(key);
    client_.sync_commit();
    reply.wait();

    return reply.get().as_string();
  } else {
    return "";
  }
#else
  return "";
#endif
}

void Redis::set(std::string key, std::string value, int expire_seconds) {
#ifdef VORTEX_HAS_FEATURE_REDIS
  if (enabled && client_.is_connected()) {
    client_.set(key, value);

    client_.sync_commit();

    if (expire_seconds > 0) {
      expire(key, expire_seconds);
    }
  }
#endif
}

bool Redis::exists(std::string key) {
#ifdef VORTEX_HAS_FEATURE_REDIS
  if (enabled && client_.is_connected()) {
    std::vector<std::string> keys;
    keys.push_back(key);

    std::future<cpp_redis::reply> reply = client_.exists(keys);
    client_.sync_commit();
    reply.wait();

    return reply.get().as_integer() == 1;
  } else {
    return false;
  }
#else
  return false;
#endif
}

void Redis::del(std::string key) {
#ifdef VORTEX_HAS_FEATURE_REDIS
  if (enabled && client_.is_connected()) {
    std::vector<std::string> keys;
    keys.push_back(key);

    client_.del(keys);
    client_.sync_commit();
  }
#endif
}

void Redis::expire(std::string key, int seconds) {
#ifdef VORTEX_HAS_FEATURE_REDIS
  if (enabled && client_.is_connected()) {
    client_.expire(key, seconds);
    client_.sync_commit();
  }
#endif
}

}  // namespace redis
}  // namespace core
}  // namespace vortex
