#ifndef VORTEX_CORE_CACHE_BACKENDS_MEMORYCACHEBACKEND_H
#define VORTEX_CORE_CACHE_BACKENDS_MEMORYCACHEBACKEND_H

#include <list>
#include <boost/unordered_map.hpp>
#include <Core/Cache/ICacheBackend.h>
#include <Maze/Object.hpp>

namespace Vortex {
    namespace Core {
        namespace Cache {
            namespace Backends {
                struct MemoryCacheEntry {
                    long long expiry_timestamp;
                    std::string value;
                };

                typedef std::pair<std::string, MemoryCacheEntry> MemoryCacheEntryPair;
                typedef std::list<MemoryCacheEntryPair> MemoryCacheList;
                typedef boost::unordered_map<std::string, MemoryCacheList::iterator> MemoryCacheMap;

                class MemoryCacheBackend : public ICacheBackend {
                private:
                    Maze::Object cache_config_;
                    bool enabled_ = false;
                    MemoryCacheList cache_list_;
                    MemoryCacheMap cache_map_;


                public:
                    MemoryCacheBackend();
                    MemoryCacheBackend(const Maze::Object& cache_config);
                    ~MemoryCacheBackend();

                    void set_config(const Maze::Object& cache_config);
                    const bool is_enabled() const;

                    virtual std::string get(const std::string& key);
                    virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180);
                    virtual bool exists(const std::string& key);
                    virtual void remove(const std::string& key);
                    virtual void set_expiry(const std::string& key, int seconds);

                private:
                    long long get_current_time_millis() const;
                };

                Core::Cache::ICacheBackend* get_memory_cache_backend();

                static const Core::Cache::CacheBackendDetails memory_cache_exports = {
                    "MemoryCacheBackend",
                    "MemoryCache",
                    get_memory_cache_backend
                };
            }  // namespace Backends
        }  // namespace Cache
    }  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_CACHE_BACKENDS_MEMORYCACHEBACKEND_H
