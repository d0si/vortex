#include <Core/GlobalRuntime.h>

namespace Vortex::Core {

    Storage::Storage* GlobalRuntime::storage() {
        return &_storage;
    }

    Caching::Cache* GlobalRuntime::cache() {
        return &_cache;
    }

    GlobalRuntime& GlobalRuntime::instance() {
        return s_instance;
    }

    GlobalRuntime GlobalRuntime::s_instance;

}
