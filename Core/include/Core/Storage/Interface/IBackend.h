#ifndef VORTEX_CORE_STORAGE_INTERFACE_IBACKEND_H
#define VORTEX_CORE_STORAGE_INTERFACE_IBACKEND_H

#include <string>
#include <Maze/Object.hpp>
#include <Core/Storage/Interface/IDatabase.h>
#include <Core/Storage/Interface/ICollection.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Interface {
				class IBackend {
				public:
					IBackend() {};
					IBackend(const Maze::Object& config) {};
					virtual ~IBackend() {};

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
				};

				typedef IBackend* (*GetBackendInstanceFunc)();

				struct BackendDetails {
					const char* class_name;
					const char* backend_name;
					GetBackendInstanceFunc get_backend_instance;
				};
			}  // namespace Interface
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_INTERFACE_IBACKEND_H
