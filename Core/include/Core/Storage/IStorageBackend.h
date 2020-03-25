#ifndef VORTEX_CORE_STORAGE_ISTORAGEBACKEND_H
#define VORTEX_CORE_STORAGE_ISTORAGEBACKEND_H

#include <string>
#include <vector>
#include <Maze/Object.hpp>

namespace Vortex {
	namespace Core {
		namespace Storage {
				class IStorageBackend {
				public:
					IStorageBackend() {};
					IStorageBackend(const Maze::Object& config) {};
					virtual ~IStorageBackend() {};

					// Simple query
					virtual void simple_insert(std::string database, std::string collection, std::string json_value) = 0;
					virtual std::string simple_find_all(std::string database, std::string collection, std::string json_simple_query) = 0;
					virtual std::string simple_find_first(std::string database, std::string collection, std::string json_simple_query) = 0;
					virtual void simple_replace_first(std::string database, std::string collection, std::string json_simple_query, std::string replacement_json_value) = 0;
					virtual void simple_delete_all(std::string database, std::string collection, std::string json_simple_query) = 0;
					virtual void simple_delete_first(std::string database, std::string collection, std::string json_simple_query) = 0;

					// Basic CRUD methods
					// virtual void insert(std::string database, std::string collection, std::string value) = 0;
					// virtual std::string find(std::string database, std::string collection, std::string query) = 0;
					// virtual void update(std::string database, std::string collection, std::string query, std::string new_value) = 0;
					// virtual void remove(std::string database, std::string collection, std::string query) = 0;

					virtual std::vector<std::string> get_database_list() = 0;
					virtual std::vector<std::string> get_collection_list(std::string database) = 0;
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
