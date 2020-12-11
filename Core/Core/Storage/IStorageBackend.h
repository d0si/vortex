#ifndef VORTEX_CORE_STORAGE_ISTORAGEBACKEND_H
#define VORTEX_CORE_STORAGE_ISTORAGEBACKEND_H

#include <string>
#include <vector>
#include <Maze/Maze.hpp>

namespace Vortex {
	namespace Core {
		namespace Storage {
				class IStorageBackend {
				public:
					IStorageBackend() {};
					IStorageBackend(const Maze::Element& config) {};
					virtual ~IStorageBackend() {};

					// Simple query
					virtual void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) = 0;
					virtual std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;
					virtual std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;
					virtual void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) = 0;
					virtual void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;
					virtual void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;

					// Basic CRUD methods
					// virtual void insert(std::string database, std::string collection, std::string value) = 0;
					// virtual std::string find(std::string database, std::string collection, std::string query) = 0;
					// virtual void update(std::string database, std::string collection, std::string query, std::string new_value) = 0;
					// virtual void remove(std::string database, std::string collection, std::string query) = 0;

					virtual std::vector<std::string> get_database_list() = 0;
					virtual std::vector<std::string> get_collection_list(const std::string& database) = 0;

					virtual bool database_exists(const std::string& database) = 0;
					virtual bool collection_exists(const std::string& database, const std::string& collection) = 0;
				};

				typedef IStorageBackend* (*GetStorageBackendInstanceFunc)();

				struct StorageBackendDetails {
					const char* class_name;
					const char* backend_name;
					GetStorageBackendInstanceFunc get_backend_instance;
				};
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_ISTORAGEBACKEND_H
