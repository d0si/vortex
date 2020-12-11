#pragma once

#include <mutex>
#include <string>
#include <vector>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core::Caching {

    class CacheBackendInterface {
    public:
        VORTEX_CORE_API virtual ~CacheBackendInterface() = default;

        VORTEX_CORE_API virtual const std::string get(const std::string& key) = 0;
        VORTEX_CORE_API virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180) = 0;
        VORTEX_CORE_API virtual bool exists(const std::string& key) = 0;
        VORTEX_CORE_API virtual void remove(const std::string& key) = 0;
        VORTEX_CORE_API virtual void set_expiry(const std::string& key, int seconds) = 0;
    };


    VORTEX_CORE_API typedef CacheBackendInterface* (*GetCacheBackendInstanceFunction)();


    struct VORTEX_CORE_API CacheBackendDetails {
        const char* class_name;
        const char* backend_name;
        GetCacheBackendInstanceFunction get_backend_instance;
    };


    class Cache {
    public:
        VORTEX_CORE_API void initialize(const Maze::Element& cache_config);
        VORTEX_CORE_API const bool is_initialized() const;

        VORTEX_CORE_API const std::string get(const std::string& key) const;
        VORTEX_CORE_API void set(const std::string& key, const std::string& value, int expire_seconds = 180) const;
        VORTEX_CORE_API bool exists(const std::string& key) const;
        VORTEX_CORE_API void remove(const std::string& key) const;
        VORTEX_CORE_API void set_expiry(const std::string& key, int seconds) const;

        VORTEX_CORE_API CacheBackendInterface* get_backend() const;
        VORTEX_CORE_API CacheBackendInterface* get_backend(const std::string& backend_name) const;

    private:
        std::vector<std::pair<std::string, CacheBackendInterface*>> _available_backends;
        std::string _default_backend;
        Maze::Element _cache_config;
        bool _initialized = false;
        std::mutex _mtx;
    };

}  // namespace Vortex::Core::Caching
