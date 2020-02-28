SET(core_SRC
    src/Core/Framework.cpp
    src/Core/CommonRuntime.cpp
    src/Core/Router.cpp
    src/Core/Host.cpp
    src/Core/Application.cpp
    src/Core/Controller.cpp
    src/Core/View.cpp

    src/Core/Storage/Storage.cpp
    src/Core/Storage/Mongo/Mongo.cpp
    src/Core/Storage/Mongo/Db.cpp
    src/Core/Storage/Mongo/Collection.cpp
    src/Core/Storage/Mongo/MongoBackend.cpp
    src/Core/Storage/Filesystem/Filesystem.cpp
    src/Core/Storage/Filesystem/Database.cpp
    src/Core/Storage/Filesystem/Collection.cpp
    src/Core/Storage/Filesystem/FilesystemBackend.cpp

    src/Core/Cache/Redis.cpp

    src/Core/Script/Script.cpp
    src/Core/Script/Duktape.cpp

    src/Core/Util/Time.cpp
    src/Core/Util/Random.cpp
    src/Core/Util/Password.cpp
    src/Core/Util/String.cpp
    src/Core/Util/Hash.cpp
)
