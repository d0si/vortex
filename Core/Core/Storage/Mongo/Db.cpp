#include <Core/Storage/Mongo/Db.h>

namespace Vortex::Core::Storage::Mongo {

	Db::Db() {}

#ifdef VORTEX_HAS_FEATURE_MONGO
	Db::Db(mongocxx::database database) 
		: _database(database) {}
#endif

	Collection Db::get_collection(const std::string& collection_name) {
#ifdef VORTEX_HAS_FEATURE_MONGO
		return Collection(_database[collection_name]);
#else
		return Collection();
#endif
	}

	std::vector<std::string> Db::list_collections() {
		std::vector<std::string> collections;

#ifdef VORTEX_HAS_FEATURE_MONGO
		auto colls = _database.list_collections();
		for (auto it = colls.begin(); it != colls.end(); it++) {
			collections.push_back((*it)["name"].get_utf8().value.to_string());
		}
#endif

		return collections;
	}

	void Db::drop_database() {
#ifdef VORTEX_HAS_FEATURE_MONGO
		_database.drop();
#endif
	}

}
