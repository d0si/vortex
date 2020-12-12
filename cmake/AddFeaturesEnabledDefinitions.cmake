#
# This script adds target compile definitions for all features enabled in Vortex.
#


if (VORTEX_ENABLE_FEATURE_REDIS)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC HAS_FEATURE_CPPREDIS=1
    )
endif()
if (VORTEX_ENABLE_FEATURE_CRYPTOPP)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC HAS_FEATURE_CRYPTOPP=1
    )
endif()
if (VORTEX_ENABLE_FEATURE_DELTASCRIPT)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC HAS_FEATURE_DELTASCRIPT=1
    )
endif()
if (VORTEX_ENABLE_FEATURE_DUKTAPE)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC HAS_FEATURE_DUKTAPE=1
    )
endif()
if (VORTEX_ENABLE_FEATURE_MONGO)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC HAS_FEATURE_MONGOCXX=1
    )
endif()
target_compile_definitions(${PROJECT_NAME}
    PRIVATE HAS_FEATURE_MAZE=1
)
