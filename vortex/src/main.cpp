#include <Vortex/Vortex.h>

int main(int argc, char** args) {
	Vortex::start_vortex(std::vector<std::string>(args, args + argc));

	return 0;
}
