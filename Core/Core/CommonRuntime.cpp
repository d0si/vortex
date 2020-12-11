#include <Core/CommonRuntime.h>

namespace Vortex::Core {

    CommonRuntime::CommonRuntime() {}

    CommonRuntime::~CommonRuntime() {}

    Storage::Storage* CommonRuntime::storage() {
        return &_storage;
    }

    Caching::Cache* CommonRuntime::cache() {
        return &_cache;
    }

    CommonRuntime CommonRuntime::s_instance;

}
