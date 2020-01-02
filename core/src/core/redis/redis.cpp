#include <core/redis/redis.h>

namespace vortex {
namespace core {
namespace redis {

redis::redis() {

}

redis::~redis() {
  if (client_.is_connected()) {
    client_.sync_commit();
    client_.disconnect();
  }
}

void redis::connect() {
  client_.connect("127.0.0.1", 6379);
}

std::string redis::get(std::string key) {
  if (client_.is_connected()) {
    std::future<cpp_redis::reply> reply = client_.get(key);
    client_.sync_commit();
    reply.wait();

    return reply.get().as_string();
  } else {
    return "";
  }
}

void redis::set(std::string key, std::string value, int expire_seconds) {
  if (client_.is_connected()) {
    client_.set(key, value);

    client_.sync_commit();

    if (expire_seconds > 0) {
      expire(key, expire_seconds);
    }
  }
}

bool redis::exists(std::string key) {
  if (client_.is_connected()) {
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
  if (client_.is_connected()) {
    std::vector<std::string> keys;
    keys.push_back(key);

    client_.del(keys);
    client_.sync_commit();
  }
}

void redis::expire(std::string key, int seconds) {
  if (client_.is_connected()) {
    client_.expire(key, seconds);
    client_.sync_commit();
  }
}

}  // namespace redis
}  // namespace core
}  // namespace vortex
