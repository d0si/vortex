#ifndef VORTEX_CORE_REDIS_REDIS_H
#define VORTEX_CORE_REDIS_REDIS_H

#include <cpp_redis/cpp_redis>

namespace vortex {
namespace core {
namespace redis {

class redis {
 private:
  cpp_redis::client client_;

 public:
  redis();
  ~redis();

  void connect();
  std::string get(std::string key);
  void set(std::string key, std::string value);
};

}  // namespace redis
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_REDIS_REDIS_H