SET(core_SRC
    src/core/framework.cpp
    src/core/router.cpp
    src/core/host.cpp
    src/core/application.cpp
    src/core/controller.cpp
    src/core/view.cpp

    src/core/storage/storage.cpp
    src/core/storage/mongo/mongo.cpp
    src/core/storage/mongo/db.cpp
    src/core/storage/mongo/collection.cpp
    src/core/storage/filesystem/filesystem.cpp
    src/core/storage/filesystem/database.cpp
    src/core/storage/filesystem/collection.cpp

    src/core/cache/redis.cpp

    src/core/script/script.cpp
    src/core/script/duktape.cpp

    src/core/util/time.cpp
    src/core/util/random.cpp
    src/core/util/password.cpp
    src/core/util/string.cpp
    src/core/util/hash.cpp
)
