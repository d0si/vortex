#pragma once

#include <Core/Caching/Cache.hpp>
#include <Maze/Maze.hpp>

namespace Vortex::Core::Caching::Backends {

    class DummyCacheBackend : public CacheBackendInterface {
    public:
        virtual const std::string get(const std::string& key) override;
        virtual void set(const std::string& key, const std::string& value, int expire_seconds = 180) override;
        virtual bool exists(const std::string& key) override;
        virtual void remove(const std::string& key) override;
        virtual void set_expiry(const std::string& key, int seconds) override;
    };


    CacheBackendInterface* get_dummy_cache_backend();


    static const CacheBackendDetails dummy_cache_exports = {
        "DummyCacheBackend",
        "DummyCache",
        get_dummy_cache_backend
    };

}  // namespace Vortex::Core::Caching::Backends
