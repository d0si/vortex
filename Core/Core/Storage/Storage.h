#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core::Storage {

    class StorageBackendInterface {
    public:
        VORTEX_CORE_API virtual ~StorageBackendInterface() {};

        // Simple query
        VORTEX_CORE_API virtual void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) = 0;
        VORTEX_CORE_API virtual const std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;
        VORTEX_CORE_API virtual const std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;
        VORTEX_CORE_API virtual void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) = 0;
        VORTEX_CORE_API virtual void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;
        VORTEX_CORE_API virtual void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) = 0;

        // Basic CRUD methods
        // virtual void insert(std::string database, std::string collection, std::string value) = 0;
        // virtual std::string find(std::string database, std::string collection, std::string query) = 0;
        // virtual void update(std::string database, std::string collection, std::string query, std::string new_value) = 0;
        // virtual void remove(std::string database, std::string collection, std::string query) = 0;

        VORTEX_CORE_API virtual const std::vector<std::string> get_database_list() = 0;
        VORTEX_CORE_API virtual const std::vector<std::string> get_collection_list(const std::string& database) = 0;

        VORTEX_CORE_API virtual bool database_exists(const std::string& database) = 0;
        VORTEX_CORE_API virtual bool collection_exists(const std::string& database, const std::string& collection) = 0;
    };


    typedef StorageBackendInterface* (*GetStorageBackendInstanceFunction)();


    struct VORTEX_CORE_API StorageBackendDetails {
        const char* class_name;
        const char* backend_name;
        GetStorageBackendInstanceFunction get_backend_instance;
    };


    class Storage {
    public:
        VORTEX_CORE_API void initialize(const Maze::Element& storage_config);
        VORTEX_CORE_API const bool is_initialized() const;

        VORTEX_CORE_API StorageBackendInterface* get_backend();
        VORTEX_CORE_API StorageBackendInterface* get_backend(const std::string& backend_name);

    private:
        std::vector<std::pair<std::string, StorageBackendInterface*>> _available_backends;
        std::string _default_backend;
        Maze::Element _storage_config;
        bool _initialized = false;
        std::mutex _mtx;
    };

}  // namespace Vortex::Core::Storage
