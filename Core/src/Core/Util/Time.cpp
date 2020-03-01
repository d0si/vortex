#include <Core/Util/Time.h>
#include <time.h>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace Time {
				int get_now() {
					return ::time(nullptr);
				}

				int get_diff(int time) {
					return get_diff(get_now(), time);
				}

				int get_diff(int time_1, int time_2) {
					return difftime(time_1, time_2);
				}

				std::string to_string(int time) {
					char time_buf[21];
					time_t raw_time = time;
					strftime(time_buf, 21, "%Y-%m-%d %H:%M:%S", gmtime(&raw_time));

					return time_buf;
				}

				std::string get_now_string() {
					return to_string(get_now());
				}
			}  // namespace Time
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex
