#include <Core/Storage/Mongo/Collection.h>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <bsoncxx/json.hpp>
#endif
#include <Maze/Element.hpp>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				Collection::Collection() {

				}

#ifdef VORTEX_HAS_FEATURE_MONGO
				Collection::Collection(mongocxx::collection collection) : collection_(collection) {

				}
#endif

				Maze::Array Collection::find(Maze::Object query) {
					return find(query.to_json());
				}

				Maze::Array Collection::find(std::string json_query) {
					Maze::Array results;

#ifdef VORTEX_HAS_FEATURE_MONGO
					auto values = collection_.find(bsoncxx::from_json(json_query));
					for (auto it = values.begin(); it != values.end(); it++) {
						results << Maze::Object::from_json(bsoncxx::to_json(*it));
					}
#endif

					return results;
				}

				Maze::Object Collection::find_by_id(std::string oid) {
					Maze::Object query;
					query.set("_id", Maze::Object("$oid", oid));

					return find_one(query);
				}

				Maze::Object Collection::find_one(Maze::Object query) {
					return find_one(query.to_json());
				}

				Maze::Object Collection::find_one(std::string json_query) {
#ifdef VORTEX_HAS_FEATURE_MONGO
					auto value = collection_.find_one(bsoncxx::from_json(json_query));

					if (value) {
						return Maze::Object::from_json(bsoncxx::to_json(value.value()));
					}
#endif

					return Maze::Object();
				}

				void Collection::delete_one(Maze::Object query) {
					delete_one(query.to_json());
				}

				void Collection::delete_one(std::string json_query) {
#ifdef VORTEX_HAS_FEATURE_MONGO
					collection_.delete_one(bsoncxx::from_json(json_query));
#endif
				}

				void Collection::delete_many(Maze::Object query) {
					delete_many(query.to_json());
				}

				void Collection::delete_many(std::string json_query) {
#ifdef VORTEX_HAS_FEATURE_MONGO
					collection_.delete_many(bsoncxx::from_json(json_query));
#endif
				}

				void Collection::insert_one(Maze::Object value) {
					insert_one(value.to_json());
				}

				void Collection::insert_one(std::string json_value) {
#ifdef VORTEX_HAS_FEATURE_MONGO
					collection_.insert_one(bsoncxx::from_json(json_value));
#endif
				}

				void Collection::insert_many(Maze::Array values) {
					std::vector<std::string> json_values;

					for (auto it = values.begin(); it != values.end(); it++) {
						json_values.push_back(it->to_json());
					}

					insert_many(json_values);
				}

				void Collection::insert_many(std::vector<std::string> json_values_array) {
#ifdef VORTEX_HAS_FEATURE_MONGO
					std::vector<bsoncxx::document::value> bson_values;

					for (auto it = json_values_array.begin(); it != json_values_array.end(); it++) {
						bson_values.push_back(bsoncxx::from_json(*it));
					}

					collection_.insert_many(bson_values);
#endif
				}

				void Collection::replace_one(Maze::Object query, Maze::Object replacement_value) {
					replace_one(query.to_json(), replacement_value.to_json());
				}

				void Collection::replace_one(std::string json_query, std::string json_replacement_value) {
#ifdef VORTEX_HAS_FEATURE_MONGO
					collection_.replace_one(bsoncxx::from_json(json_query), bsoncxx::from_json(json_replacement_value));
#endif
				}
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
