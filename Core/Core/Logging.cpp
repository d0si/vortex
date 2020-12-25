#include <Core/Logging.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Vortex::Core::Logging {

    std::shared_ptr<spdlog::logger> Logger::s_logger;

    void Logger::initialize() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_logger = spdlog::stdout_color_mt("Vortex");
        s_logger->set_level(spdlog::level::trace);
        s_logger->trace("Logger initialized");
    }

    std::shared_ptr<spdlog::logger>& Logger::logger() {
        if (!s_logger)
            initialize();

        return s_logger;
    }

}
