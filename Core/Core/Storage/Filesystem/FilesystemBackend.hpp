#pragma once

#include <Core/Storage/Storage.hpp>
#include <Maze/Maze.hpp>

namespace Vortex::Core::Storage::Filesystem {

    class FilesystemBackend : public StorageBackendInterface {
    public:
        VORTEX_CORE_API FilesystemBackend();
        VORTEX_CORE_API ~FilesystemBackend();

        VORTEX_CORE_API void set_config(const Maze::Element& filesystem_config);

        // Simple query
        VORTEX_CORE_API virtual void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) override;
        VORTEX_CORE_API virtual const std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;
        VORTEX_CORE_API virtual const std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;
        VORTEX_CORE_API virtual void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) override;
        VORTEX_CORE_API virtual void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;
        VORTEX_CORE_API virtual void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) override;

        VORTEX_CORE_API virtual const std::vector<std::string> get_database_list() override;
        VORTEX_CORE_API virtual const std::vector<std::string> get_collection_list(const std::string& database) override;

        VORTEX_CORE_API virtual bool database_exists(const std::string& database) override;
        VORTEX_CORE_API virtual bool collection_exists(const std::string& database, const std::string& collection) override;

    private:
        Maze::Element _filesystem_config;
        bool _cache_enabled = false;
        bool _in_memory_only = false;
        int _cache_expiry = 60;

        bool check_if_matches_simple_query(const Maze::Element& value, Maze::Element simple_query) const;
        Maze::Element get_collection_entries(const std::string& database, const std::string& collection) const;
        void save_collection_entries(const std::string& database, const std::string& collection, const Maze::Element& values) const;
    };


    StorageBackendInterface* get_filesystem_backend();


    static const Core::Storage::StorageBackendDetails filesystem_exports = {
        "FilesystemBackend",
        "Filesystem",
        get_filesystem_backend
    };

}  // namespace Vortex::Core::Storage::Filesystem
