#include <Core/Util/Time.hpp>
#include <time.h>

namespace Vortex::Core::Util {
    int Time::get_now() {
        return (int)::time(nullptr);
    }

    int Time::get_diff(const int time) {
        return get_diff(get_now(), time);
    }

    int Time::get_diff(const int time_1, const int time_2) {
        return (int)difftime(time_1, time_2);
    }

    const std::string Time::to_string(const int time) {
        char time_buf[21];
        time_t raw_time = time;
#pragma warning(push)
#pragma warning(disable: 4996)  // TODO: gmtime may be unsafe -> gmtime_s
        strftime(time_buf, 21, "%Y-%m-%d %H:%M:%S", gmtime(&raw_time));
#pragma warning(pop)

        return time_buf;
    }

    const std::string Time::get_now_string() {
        return to_string(get_now());
    }

}
