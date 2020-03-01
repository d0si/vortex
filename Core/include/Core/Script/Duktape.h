#ifndef VORTEX_CORE_SCRIPT_DUKTAPE_H
#define VORTEX_CORE_SCRIPT_DUKTAPE_H

#include <string>

namespace duk {
	class Context;
}

namespace Vortex {
	namespace Core {
		class Framework;

		namespace Script {
			class Duktape {
			private:
				duk::Context* ctx_;
				Framework* framework_;

			public:
				Duktape(Framework* framework);
				~Duktape();

				void setup();
				void exec(std::string script);
			};
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_SCRIPT_DUKTAPE_H
