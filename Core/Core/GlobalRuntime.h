#pragma once

#include <Core/DLLSupport.h>
#include <Core/Storage/Storage.h>
#include <Core/Caching/Cache.h>

namespace Vortex::Core {

    class GlobalRuntime {
    public:
        VORTEX_CORE_API Storage::Storage* storage();
        VORTEX_CORE_API Caching::Cache* cache();

        VORTEX_CORE_API static GlobalRuntime& instance();

    private:
        Storage::Storage _storage;
        Caching::Cache _cache;

        static GlobalRuntime s_instance;
    };

}  // namespace Vortex::Core
