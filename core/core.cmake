SET(core_SRC
    src/core/framework/framework.cpp
    src/core/framework/router.cpp
    src/core/framework/host.cpp
    src/core/framework/application.cpp
    src/core/framework/controller.cpp
    src/core/framework/view.cpp

    src/core/mongo/mongo.cpp
    src/core/mongo/db.cpp
    src/core/mongo/collection.cpp

    src/core/redis/redis.cpp

    src/core/script/script.cpp
    src/core/script/duktape.cpp

    src/core/util/time.cpp
    src/core/util/random.cpp
    src/core/util/password.cpp
)
