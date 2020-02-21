#include <core/util/random.h>
#include <random>
#include <fcntl.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <io.h>
#else
#include <unistd.h>
#endif

namespace vortex {
	namespace core {
		namespace util {
			namespace random {
				std::string random_string(unsigned int length, const std::string char_list) {
					thread_local static std::mt19937 rg{ std::random_device{}() };
					thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, char_list.length() - 2);

					std::string s;
					s.reserve(length);

					while (length--)
						s += char_list[pick(rg)];

					return s;
				}


				int rand_bytes(void* const byte_buf, const size_t byte_len) {
					int fd = open("/dev/urandom", O_RDONLY);
					if (fd < 0) {
						return -1;
						//throw runtime_error{ "RandBytes(): failed to open" };
					}

					int rd_len = 0;
					while (rd_len < byte_len) {
						int n = read(fd, byte_buf, byte_len);
						if (n < 0) {
							return -2;
							/*stringstream ss;
							ss << "RandBytes(): failed (n=" << n << ") " << "(rd_len=" << rd_len << ")";
							throw runtime_error{ ss.str() };*/
						}
						rd_len += n;
					}

					close(fd);
					return 0;
				}
			}  // namespace random
		}  // namespace util
	}  // namespace core
}  // namespace vortex
