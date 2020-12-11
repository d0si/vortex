//#include <Vortex/Vortex.h>

#include <iostream>
#include <Core/Util/Time.h>
#include <Core/Util/String.h>
#include <Core/Caching/Cache.h>
#include <Core/Exceptions/StorageException.h>

int main(int argc, char** args) {
    //	Vortex::start_vortex(std::vector<std::string>(args, args + argc));

    Vortex::Core::Caching::Cache interface;
    interface.initialize(Maze::Element::from_json(R"(
{
	"enabled": true,
	"config": {
		"MemoryCache": {
			"enabled": true
		}
	}
}
)"));

    std::string aa;
    {
        interface.set("test_1", "val_1");
        aa = interface.get("test_1");
    }

    std::cout << aa << std::endl;

    std::cin.get();
    return 0;
}
