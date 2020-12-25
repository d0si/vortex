#pragma once

#include <Core/DLLSupport.h>
#include <memory>
#include <spdlog/spdlog.h>

namespace Vortex::Core::Logging {

    class Logger {
    public:
        VORTEX_CORE_API static void initialize();

        VORTEX_CORE_API static std::shared_ptr<spdlog::logger>& logger();

    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };

}  // namespace Vortex::Core::Logging

#define VORTEX_TRACE(...)       ::Vortex::Core::Logging::Logger::logger()->trace(__VA_ARGS__)
#define VORTEX_INFO(...)        ::Vortex::Core::Logging::Logger::logger()->info(__VA_ARGS__)
#define VORTEX_WARN(...)        ::Vortex::Core::Logging::Logger::logger()->warn(__VA_ARGS__)
#define VORTEX_ERROR(...)       ::Vortex::Core::Logging::Logger::logger()->error(__VA_ARGS__)
#define VORTEX_CRITICAL(...)    ::Vortex::Core::Logging::Logger::logger()->critical(__VA_ARGS__)
