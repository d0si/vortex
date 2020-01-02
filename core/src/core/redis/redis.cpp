#include <core/redis/redis.h>

namespace vortex {
namespace core {
namespace redis {

redis::redis() {

}

redis::~redis() {
  client_.disconnect();
}

void redis::connect() {
  client_.connect("127.0.0.1", 6379);
}

std::string redis::get(std::string key) {
  auto reply = client_.get(key);
  reply.wait();
  return reply.get().as_string();
}

void redis::set(std::string key, std::string value) {
  client_.set(key, value);

  client_.sync_commit();
}

}  // namespace redis
}  // namespace core
}  // namespace vortex
