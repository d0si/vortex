#pragma once

#include <Core/DLLSupport.hpp>

#ifdef VORTEX_CORE_EXPORTS
#define VORTEX_SERVER_API __DLL_EXPORT
#else
#define VORTEX_SERVER_API __DLL_IMPORT
#endif
