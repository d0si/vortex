#include <Vortex/Vortex.h>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/instance.hpp>
#endif

int main(int argc, char** args) {
#ifdef VORTEX_HAS_FEATURE_MONGO
	mongocxx::instance instance{};
#endif

	Vortex::start_vortex(std::vector<std::string>(args, args + argc));

	return 0;
}
