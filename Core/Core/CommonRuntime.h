#pragma once

#include <Core/Storage/Storage.h>
#include <Core/Caching/Cache.h>

namespace Vortex::Core {

    class CommonRuntime {
    public:
        VORTEX_CORE_API CommonRuntime();
        VORTEX_CORE_API ~CommonRuntime();

        VORTEX_CORE_API Storage::Storage* storage();
        VORTEX_CORE_API Caching::Cache* cache();

        VORTEX_CORE_API inline static CommonRuntime& instance() { return s_instance; }

    private:
        Storage::Storage _storage;
        Caching::Cache _cache;

        static CommonRuntime s_instance;
    };

}  // namespace Vortex::Core
