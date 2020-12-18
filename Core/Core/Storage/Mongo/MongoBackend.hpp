#pragma once

#include <string>
#include <Core/Storage/Storage.hpp>
#include <Core/Storage/Mongo/Mongo.hpp>

namespace Vortex::Core::Storage::Mongo {

	class MongoBackend : public StorageBackendInterface {
	private:
		Core::Storage::Mongo::Mongo _client;

	public:
		MongoBackend();
		~MongoBackend();

		// Simple query
		virtual void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) override;
		virtual const std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;
		virtual const std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;
		virtual void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) override;
		virtual void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;
		virtual void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;

		virtual const std::vector<std::string> get_database_list() override;
		virtual const std::vector<std::string> get_collection_list(const std::string& database) override;

		virtual bool database_exists(const std::string& database) override;
		virtual bool collection_exists(const std::string& database, const std::string& collection) override;

		Core::Storage::Mongo::Mongo* get_client();
	};


	StorageBackendInterface* get_mongo_backend();


	static const StorageBackendDetails mongo_exports = {
		"MongoBackend",
		"Mongo",
		get_mongo_backend
	};

}  // Vortex::Core::Storage::Mongo
