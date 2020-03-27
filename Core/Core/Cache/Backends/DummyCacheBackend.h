#ifndef VORTEX_CORE_CACHE_BACKENDS_DUMMYCACHEBACKEND_H
#define VORTEX_CORE_CACHE_BACKENDS_DUMMYCACHEBACKEND_H

#include <Core/Cache/ICacheBackend.h>
#include <Maze/Object.hpp>

namespace Vortex {
    namespace Core {
        namespace Cache {
            namespace Backends {
                class DummyCacheBackend : public ICacheBackend {
                public:
                    virtual std::string get(const std::string& key);
                    virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180);
                    virtual bool exists(const std::string& key);
                    virtual void remove(const std::string& key);
                    virtual void set_expiry(const std::string& key, int seconds);
                };

                Core::Cache::ICacheBackend* get_dummy_cache_backend();

                static const Core::Cache::CacheBackendDetails dummy_cache_exports = {
                    "DummyCacheBackend",
                    "DummyCache",
                    get_dummy_cache_backend
                };
            }  // namespace Backends
        }  // namespace Cache
    }  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_CACHE_BACKENDS_DUMMYCACHEBACKEND_H
