//#include <Vortex/Vortex.h>

#include <iostream>
#include <Core/Util/Time.h>
#include <Core/Util/String.h>

int main(int argc, char** args) {
//	Vortex::start_vortex(std::vector<std::string>(args, args + argc));

	std::cout << Vortex::Core::Util::Time::get_now_string() << std::endl;
	std::cout << Vortex::Core::Util::String::trim_left( Vortex::Core::Util::Time::get_now_string() ) << std::endl;

	std::cin.get();
	return 0;
}
