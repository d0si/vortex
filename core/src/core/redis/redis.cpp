#include <core/redis/redis.h>

#include <iostream>

namespace vortex {
namespace core {
namespace redis {

redis::redis() {

}

redis::redis(const maze::object& redis_config) {
  set_config(redis_config);

  if (redis_config_.is_bool("enabled")) {
    enabled = redis_config_["enabled"].get_bool();
  }
}

redis::~redis() {
  if (client_.is_connected()) {
    client_.sync_commit();
    client_.disconnect();
  }
}

void redis::connect() {
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
}

void redis::set_config(const maze::object& redis_config) {
  redis_config_ = redis_config;
}

std::string redis::get(std::string key) {
  if (enabled && client_.is_connected()) {
    std::future<cpp_redis::reply> reply = client_.get(key);
    client_.sync_commit();
    reply.wait();

    return reply.get().as_string();
  } else {
    return "";
  }
}

void redis::set(std::string key, std::string value, int expire_seconds) {
  if (enabled && client_.is_connected()) {
    client_.set(key, value);

    client_.sync_commit();

    if (expire_seconds > 0) {
      expire(key, expire_seconds);
    }
  }
}

bool redis::exists(std::string key) {
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
}

void redis::del(std::string key) {
  if (enabled && client_.is_connected()) {
    std::vector<std::string> keys;
    keys.push_back(key);

    client_.del(keys);
    client_.sync_commit();
  }
}

void redis::expire(std::string key, int seconds) {
  if (enabled && client_.is_connected()) {
    client_.expire(key, seconds);
    client_.sync_commit();
  }
}

}  // namespace redis
}  // namespace core
}  // namespace vortex
