#include <Core/Caching/Backends/DummyCacheBackend.h>

namespace Vortex::Core::Caching::Backends {

    const std::string DummyCacheBackend::get(const std::string& key) {
        return "";
    }

    void DummyCacheBackend::set(const std::string& key, const std::string& value, int expire_seconds) {}

    bool DummyCacheBackend::exists(const std::string& key) {
        return false;
    }

    void DummyCacheBackend::remove(const std::string& key) {}

    void DummyCacheBackend::set_expiry(const std::string& key, int seconds) {}

    CacheBackendInterface* get_dummy_cache_backend() {
        static DummyCacheBackend instance;
        return &instance;
    }

}
