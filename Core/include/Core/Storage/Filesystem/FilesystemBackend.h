#ifndef VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H
#define VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H

#include <Core/Storage/Interface/IBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Filesystem {
				class FilesystemBackend: public Core::Storage::Interface::IBackend {
				private:
					Maze::Object filesystem_config_;

				public:
					FilesystemBackend();
					~FilesystemBackend();

					void set_config(const Maze::Object& filesystem_config);

					// Simple query
					virtual void simple_insert(std::string database, std::string collection, std::string json_value);
					virtual std::string simple_find_all(std::string database, std::string collection, std::string json_simple_query);
					virtual std::string simple_find_first(std::string database, std::string collection, std::string json_simple_query);
					virtual void simple_replace_first(std::string database, std::string collection, std::string json_simple_query, std::string replacement_json_value);
					virtual void simple_delete_all(std::string database, std::string collection, std::string json_simple_query);
					virtual void simple_delete_first(std::string database, std::string collection, std::string json_simple_query);

					virtual void insert(std::string database, std::string collection, std::string value);
					virtual std::string find(std::string database, std::string collection, std::string query);
					virtual void update(std::string database, std::string collection, std::string query, std::string new_value);
					virtual void remove(std::string database, std::string collection, std::string query);

				private:
					bool check_if_matches_simple_query(const Maze::Object& value, Maze::Object& simple_query) const;
				};

				Core::Storage::Interface::IBackend* get_backend();

				static const Core::Storage::Interface::BackendDetails exports = {
					"FilesystemBackend",
					"Filesystem",
					get_backend
				};
			}  // namespace Filesystem
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H
