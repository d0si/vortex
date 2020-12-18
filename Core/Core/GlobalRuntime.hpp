#pragma once

#include <Core/DLLSupport.hpp>
#include <Core/Storage/Storage.hpp>
#include <Core/Caching/Cache.hpp>

namespace Vortex::Core {

    class GlobalRuntime {
    public:
        VORTEX_CORE_API Storage::Storage& storage();
        VORTEX_CORE_API Caching::Cache& cache();

        VORTEX_CORE_API static GlobalRuntime& instance();

    private:
        Storage::Storage _storage;
        Caching::Cache _cache;

        static GlobalRuntime s_instance;
    };

}  // namespace Vortex::Core
