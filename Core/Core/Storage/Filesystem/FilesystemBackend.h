#ifndef VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H
#define VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H

#include <Core/Storage/IStorageBackend.h>
#include <Maze/Array.hpp>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Filesystem {
				class FilesystemBackend: public Core::Storage::IStorageBackend {
				private:
					Maze::Object filesystem_config_;
					bool cache_enabled_ = false;
					bool in_memory_only_ = false;
					int cache_expiry_ = 60;

				public:
					FilesystemBackend();
					~FilesystemBackend();

					void set_config(const Maze::Object& filesystem_config);

					// Simple query
					virtual void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value);
					virtual std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query);
					virtual std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query);
					virtual void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value);
					virtual void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query);
					virtual void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query);

					// virtual void insert(std::string database, std::string collection, std::string value);
					// virtual std::string find(std::string database, std::string collection, std::string query);
					// virtual void update(std::string database, std::string collection, std::string query, std::string new_value);
					// virtual void remove(std::string database, std::string collection, std::string query);

					virtual std::vector<std::string> get_database_list();
					virtual std::vector<std::string> get_collection_list(const std::string& database);

					virtual bool database_exists(const std::string& database);
					virtual bool collection_exists(const std::string& database, const std::string& collection);

				private:
					bool check_if_matches_simple_query(const Maze::Object& value, Maze::Object simple_query) const;
					Maze::Array get_collection_entries(const std::string& database, const std::string& collection) const;
					void save_collection_entries(const std::string& database, const std::string& collection, const Maze::Array& values) const;
				};

				Core::Storage::IStorageBackend* get_filesystem_backend();

				static const Core::Storage::StorageBackendDetails filesystem_exports = {
					"FilesystemBackend",
					"Filesystem",
					get_filesystem_backend
				};
			}  // namespace Filesystem
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_STORAGE_FILESYSTEM_FILESYSTEMBACKEND_H
