#include <Core/Storage/Mongo/Collection.hpp>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <bsoncxx/json.hpp>
#endif
#include <Maze/Maze.hpp>

namespace Vortex::Core::Storage::Mongo {

    Collection::Collection() {}

#ifdef VORTEX_HAS_FEATURE_MONGO
    Collection::Collection(mongocxx::collection collection)
        : _collection(collection) {}
#endif

    Maze::Element Collection::find(const Maze::Element& query) {
        return find(query.to_json());
    }

    Maze::Element Collection::find(const std::string& json_query) {
        Maze::Element results(Maze::Type::Array);

#ifdef VORTEX_HAS_FEATURE_MONGO
        auto values = _collection.find(bsoncxx::from_json(json_query));
        for (auto it = values.begin(); it != values.end(); it++) {
            results << Maze::Element::from_json(bsoncxx::to_json(*it));
        }
#endif

        return results;
    }

    Maze::Element Collection::find_by_id(const std::string& oid) {
        Maze::Element query(
            { "id" },
            { Maze::Element({ "$oid" }, { oid }) }
        );

        return find_one(query);
    }

    Maze::Element Collection::find_one(const Maze::Element& query) {
        return find_one(query.to_json());
    }

    Maze::Element Collection::find_one(const std::string& json_query) {
#ifdef VORTEX_HAS_FEATURE_MONGO
        auto value = _collection.find_one(bsoncxx::from_json(json_query));

        if (value) {
            return Maze::Element::from_json(bsoncxx::to_json(value.value()));
        }
#endif

        return Maze::Element(Maze::Type::Object);
    }

    void Collection::delete_one(const Maze::Element& query) {
        delete_one(query.to_json());
    }

    void Collection::delete_one(const std::string& json_query) {
#ifdef VORTEX_HAS_FEATURE_MONGO
        _collection.delete_one(bsoncxx::from_json(json_query));
#endif
    }

    void Collection::delete_many(const Maze::Element& query) {
        delete_many(query.to_json());
    }

    void Collection::delete_many(const std::string& json_query) {
#ifdef VORTEX_HAS_FEATURE_MONGO
        _collection.delete_many(bsoncxx::from_json(json_query));
#endif
    }

    void Collection::insert_one(const Maze::Element& value) {
        insert_one(value.to_json());
    }

    void Collection::insert_one(const std::string& json_value) {
#ifdef VORTEX_HAS_FEATURE_MONGO
        _collection.insert_one(bsoncxx::from_json(json_value));
#endif
    }

    void Collection::insert_many(const Maze::Element& values) {
        std::vector<std::string> json_values;

        for (auto it = values.begin(); it != values.end(); it++) {
            json_values.push_back(it->to_json());
        }

        insert_many(json_values);
    }

    void Collection::insert_many(const std::vector<std::string>& json_values_array) {
#ifdef VORTEX_HAS_FEATURE_MONGO
        std::vector<bsoncxx::document::value> bson_values;

        for (auto it = json_values_array.begin(); it != json_values_array.end(); it++) {
            bson_values.push_back(bsoncxx::from_json(*it));
        }

        _collection.insert_many(bson_values);
#endif
    }

    void Collection::replace_one(const Maze::Element& query, const Maze::Element& replacement_value) {
        replace_one(query.to_json(), replacement_value.to_json());
    }

    void Collection::replace_one(const std::string& json_query, const std::string& json_replacement_value) {
#ifdef VORTEX_HAS_FEATURE_MONGO
        _collection.replace_one(bsoncxx::from_json(json_query), bsoncxx::from_json(json_replacement_value));
#endif
    }

}
