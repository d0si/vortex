#pragma once

#include <string>
#include <vector>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/database.hpp>
#endif
#include <Core/Storage/Mongo/Collection.h>

namespace Vortex::Core::Storage::Mongo {

    class Mongo;


    class Db {
    public:
        Db();
#ifdef VORTEX_HAS_FEATURE_MONGO
        Db(mongocxx::database database);
#endif

        VORTEX_CORE_API Collection get_collection(const std::string& collection_name);

        VORTEX_CORE_API std::vector<std::string> list_collections();

        VORTEX_CORE_API void drop_database();

    private:
#ifdef VORTEX_HAS_FEATURE_MONGO
        mongocxx::database _database;
#endif
    };

}  // namespace Vortex::Core::Storage::Mongo
