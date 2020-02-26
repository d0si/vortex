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

					virtual IDatabase get_database(std::string database_name) = 0;
					virtual ICollection get_collection(std::string database_name, std::string collection_name) = 0;
				};

				typedef IBackend* (*GetBackendInstanceFunc)();

				struct BackendDetails {
					const char* class_name;
					const char* backend_name;
					GetBackendInstanceFunc get_backend_instance;
				};

#define VORTEX_STORAGE_BACKEND(class_type, backend_name)		\
Vortex::Core::Storage::Interface::IBackend* get_backend() {		\
	static class_type instance;									\
	return &instance;											\
}																\
Vortex::Core::Storage::Interface::BackendDetails exports = {	\
	#class_type,												\
	backend_name,												\
	get_backend,												\
};

			}  // namespace Interface
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_INTERFACE_IBACKEND_H
