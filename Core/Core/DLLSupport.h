#pragma once

#ifndef __DLL_EXPORT
#ifndef __DLL_IMPORT
    #ifdef WIN32
        #define __DLL_EXPORT __declspec(dllexport)
        #define __DLL_IMPORT __declspec(dllimport)
    #elif defined(__GNUC__)
        #define __DLL_EXPORT __attribute__((visibility("default")))
        #define __DLL_IMPORT
    #else
        #define __DLL_EXPORT
        #define __DLL_IMPORT
    #endif
#endif
#endif


#ifdef VORTEX_CORE_EXPORTS
    #define VORTEX_CORE_API __DLL_EXPORT
    #define VORTEX_CORE_API_E __DLL_EXPORT
#else
    #define VORTEX_CORE_API __DLL_IMPORT
    #define VORTEX_CORE_API_E __DLL_IMPORT
#endif

#ifdef VORTEX_APP_EXPORTS
    #define VORTEX_APP_API __DLL_EXPORT
#else
    #define VORTEX_APP_API __DLL_IMPORT
#endif
