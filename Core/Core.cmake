#
# Set source files that need to be built
#
set(CORE_SOURCES
    Core/Applications/Application.cpp

    Core/Caching/Backends/RedisBackend.cpp
    Core/Caching/Backends/MemoryCacheBackend.cpp
    Core/Caching/Backends/DummyCacheBackend.cpp
    Core/Caching/Cache.cpp

    Core/Exceptions/CacheException.cpp
    Core/Exceptions/ScriptException.cpp
    Core/Exceptions/StorageException.cpp
    Core/Exceptions/VortexException.cpp

    Core/Modules/ModuleLoader.cpp
    Core/Modules/DependencyInjection.cpp

    Core/Storage/Storage.cpp
    Core/Storage/Mongo/Mongo.cpp
    Core/Storage/Mongo/Db.cpp
    Core/Storage/Mongo/Collection.cpp
    Core/Storage/Mongo/MongoBackend.cpp
    Core/Storage/Filesystem/FilesystemBackend.cpp

    Core/Util/Hash.cpp
    Core/Util/Password.cpp
    Core/Util/Random.cpp
    Core/Util/String.cpp
    Core/Util/Time.cpp
    
    Core/GlobalRuntime.cpp

    # Testing
    Core/VortexBase.cpp
)
