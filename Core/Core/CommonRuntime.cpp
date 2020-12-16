#include <Core/CommonRuntime.h>

namespace Vortex::Core {

    Storage::Storage* CommonRuntime::storage() {
        return &_storage;
    }

    Caching::Cache* CommonRuntime::cache() {
        return &_cache;
    }

    CommonRuntime& CommonRuntime::instance() {
        return s_instance;
    }

    CommonRuntime CommonRuntime::s_instance;

}
