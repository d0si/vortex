#ifndef VORTEX_CORE_CACHE_ICACHEBACKEND_H
#define VORTEX_CORE_CACHE_ICACHEBACKEND_H

#include <string>
#include <Maze/Object.hpp>

namespace Vortex {
    namespace Core {
        namespace Cache {
            class ICacheBackend {
            public:
                ICacheBackend() {};
                ICacheBackend(const Maze::Object& config) {};
                virtual ~ICacheBackend() {};

                virtual std::string get(const std::string& key) = 0;
                virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180) = 0;
                virtual bool exists(const std::string& key) = 0;
                virtual void remove(const std::string& key) = 0;
                virtual void set_expiry(const std::string& key, int seconds) = 0;
            };

            typedef ICacheBackend* (*GetCacheBackendInstanceFunc)();

            struct CacheBackendDetails {
                const char* class_name;
                const char* backend_name;
                GetCacheBackendInstanceFunc get_backend_instance;
            };
        }  // namespace Cache
    }  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_CACHE_ICACHEBACKEND_H
