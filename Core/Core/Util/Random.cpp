#include <Core/Util/Random.hpp>
#include <random>
#include <fcntl.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <io.h>
#else
#include <unistd.h>
#endif

namespace Vortex::Core::Util {

    const std::string Random::random_string(const unsigned int length, const std::string& char_list) {
        thread_local static std::mt19937 rg{ std::random_device{}() };
        thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, char_list.length() - 2);

        std::string s;
        s.reserve(length);

        unsigned int chars_left = length;
        while (chars_left--)
            s += char_list[pick(rg)];

        return s;
    }


    int Random::rand_bytes(void* const byte_buf, const unsigned int byte_len) {
#pragma warning(push)
#pragma warning(disable: 4996)  // TODO: open - POSIX name for this item is deprecated -> _open
        int fd = open("/dev/urandom", O_RDONLY);
#pragma warning(pop)
        if (fd < 0) {
            return -1;
            //throw runtime_error{ "RandBytes(): failed to open" };
        }

        unsigned int rd_len = 0;
        while (rd_len < byte_len) {
#pragma warning(push)
#pragma warning(disable: 4996)  // TODO: read - POSIX name for this item is deprecated -> _read
            int n = read(fd, byte_buf, byte_len);
#pragma warning(pop)
            if (n < 0) {
                return -2;
                /*stringstream ss;
                ss << "RandBytes(): failed (n=" << n << ") " << "(rd_len=" << rd_len << ")";
                throw runtime_error{ ss.str() };*/
            }
            rd_len += n;
        }

#pragma warning(push)
#pragma warning(disable: 4996)  // TODO: close - POSIX name for this item is deprecated -> _close
        close(fd);
#pragma warning(pop)
        return 0;
    }

}
