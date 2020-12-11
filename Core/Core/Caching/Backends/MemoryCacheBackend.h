#pragma once

#include <list>
#include <boost/unordered_map.hpp>
#include <Core/Caching/Cache.h>
#include <Maze/Maze.hpp>

namespace Vortex::Core::Caching::Backends {
    
    struct MemoryCacheEntry {
        long long expiry_timestamp;
        std::string value;
    };


    typedef std::pair<std::string, MemoryCacheEntry> MemoryCacheEntryPair;
    typedef std::list<MemoryCacheEntryPair> MemoryCacheList;
    typedef boost::unordered_map<std::string, MemoryCacheList::iterator> MemoryCacheMap;


    class MemoryCacheBackend : public CacheBackendInterface {
    public:
        MemoryCacheBackend();
        MemoryCacheBackend(const Maze::Element& cache_config);
        ~MemoryCacheBackend();

        void set_config(const Maze::Element& cache_config);
        const bool is_enabled() const;

        virtual const std::string get(const std::string& key) override;
        virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180) override;
        virtual bool exists(const std::string& key) override;
        virtual void remove(const std::string&  key) override;
        virtual void set_expiry(const std::string& key, int seconds) override;

    private:
        Maze::Element _cache_config;
        bool _enabled = false;
        MemoryCacheList _cache_list;
        MemoryCacheMap _cache_map;

        long long get_current_time_millis() const;
    };


    CacheBackendInterface* get_memory_cache_backend();


    static const CacheBackendDetails memory_cache_exports = {
        "MemoryCacheBackend",
        "MemoryCache",
        get_memory_cache_backend
    };

}  // namespace Vortex::Core::Caching::Backends
