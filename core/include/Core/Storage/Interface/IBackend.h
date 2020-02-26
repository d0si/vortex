#ifndef VORTEX_CORE_STORAGE_INTERFACE_IBACKEND_H
#define VORTEX_CORE_STORAGE_INTERFACE_IBACKEND_H

#include <string>
#include <maze/object.h>
#include <Core/Storage/Interface/IDatabase.h>
#include <Core/Storage/Interface/ICollection.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Interface {
				class IBackend {
				public:
					IBackend() {};
					IBackend(const maze::object& config) {};
					virtual ~IBackend() {};

					// Basic CRUD methods
					virtual void insert(std::string database, std::string collection, std::string value) = 0;
					virtual std::string find(std::string database, std::string collection, std::string query) = 0;
					virtual void update(std::string database, std::string collection, std::string query, std::string new_value) = 0;
					virtual void remove(std::string database, std::string collection, std::string query) = 0;
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
