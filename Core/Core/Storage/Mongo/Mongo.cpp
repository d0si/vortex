#include <Core/Storage/Mongo/Mongo.h>

namespace Vortex::Core::Storage::Mongo {

	Mongo::Mongo() {
		connect();
	}

	Mongo::Mongo(const Maze::Element& mongo_config) {
		set_config(mongo_config);
		connect();
	}

	void Mongo::connect() {
#ifdef VORTEX_HAS_FEATURE_MONGO
		if (enabled) {
			mongocxx::uri uri{ get_connection_uri() };

			client_ = mongocxx::client{ uri };
		}
#endif
	}

	void Mongo::set_config(const Maze::Element& mongo_config) {
		_mongo_config = mongo_config;

		if (_mongo_config.is_bool("enabled")) {
			_enabled = _mongo_config["enabled"].get_bool();
		}
	}

	std::string Mongo::get_connection_uri() {
		std::string uri = "mongodb://";

		if (_mongo_config.is_string("username") && _mongo_config.is_string("password")) {
			uri += _mongo_config["username"].get_string() + ":" +
				_mongo_config["password"].get_string() + "@";
		}

		if (_mongo_config.is_string("host")) {
			uri += _mongo_config["host"].get_string();
		}
		else {
			uri += "localhost";
		}

		if (_mongo_config.is_int("port")) {
			int port = _mongo_config["port"].get_int();

			if (port > 0) {
				uri += ":" + std::to_string(port);
			}
		}

		if (_mongo_config.is_string("database")) {
			uri += "/" + _mongo_config["database"].get_string();
		}

		return uri;
	}

	std::string Mongo::get_default_db_name() {
		if (_mongo_config.is_string("default_database")) {
			return _mongo_config["default_database"].get_string();
		}
		else if (_mongo_config.is_string("database")) {
			return _mongo_config["database"].get_string();
		}
		else {
			return "vortex";
		}
	}

	Db Mongo::get_db(const std::string& database_name) {
#ifdef VORTEX_HAS_FEATURE_MONGO
		return Db(_client[database_name]);
#else
		return Db();
#endif
	}

	Collection Mongo::get_collection(const std::string& collection_name) {
		return get_collection(get_default_db_name(), collection_name);
	}

	Collection Mongo::get_collection(const std::string& database_name, const std::string& collection_name) {
#ifdef VORTEX_HAS_FEATURE_MONGO
		return Collection(_client[database_name][collection_name]);
#else
		return Collection();
#endif
	}

	std::vector<std::string> Mongo::list_databases() {
		std::vector<std::string> databases;

#ifdef VORTEX_HAS_FEATURE_MONGO
		auto dbs = _client.list_databases();
		for (auto it = dbs.begin(); it != dbs.end(); it++) {
			databases.push_back((*it)["name"].get_utf8().value.to_string());
		}
#endif

		return databases;
	}

	std::vector<std::string> Mongo::list_collections(const std::string& database_name) {
		Db db = get_db(database_name);

		return db.list_collections();
	}

	bool Mongo::database_exists(const std::string& database) {
		for (auto db : list_databases()) {
			if (db == database) {
				return true;
			}
		}

		return false;
	}

	bool Mongo::collection_exists(const std::string& database, const std::string& collection) {
#ifdef VORTEX_HAS_FEATURE_MONGO
		return _client[database].has_collection(collection);
#else
		return false;
#endif
	}

	void Mongo::drop_database(const std::string& database_name) {
		Db db = get_db(database_name);
		db.drop_database();
	}

	void Mongo::clone_database(const std::string& old_name, const std::string& new_name) {
		if (old_name == new_name) {
			return;
		}

		Db old_db = get_db(old_name);
		Db new_db = get_db(new_name);

		std::vector<std::string> collection_list = old_db.list_collections();
		for (auto it = collection_list.begin(); it != collection_list.end(); it++) {
			Collection old_collection = old_db.get_collection(*it);
			Collection new_collection = new_db.get_collection(*it);

			Maze::Element old_values = old_collection.find(std::string("{}"));

			new_collection.insert_many(old_values);
		}
	}

	const bool Mongo::is_enabled() const {
		return _enabled;
	}

}
