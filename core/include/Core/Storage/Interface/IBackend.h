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
					IBackend();
					IBackend(const maze::object& config);

					IDatabase get_database(std::string database_name);
					ICollection get_collection(std::string database_name, std::string collection_name);
				};
			}  // namespace Interface
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_INTERFACE_IBACKEND_H
