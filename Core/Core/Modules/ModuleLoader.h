#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <Core/DllSupport.h>
#include <Core/Modules/Module.h>

namespace Vortex::Core::Modules {

	class ModuleLoader {
	public:
		VORTEX_CORE_API virtual ~ModuleLoader() = default;

		VORTEX_CORE_API virtual Module* load_module(const std::string& module_name) = 0;
		VORTEX_CORE_API virtual Module* get_module(const std::string& module_name) = 0;
		VORTEX_CORE_API virtual bool module_loaded(const std::string& module_name) = 0;

		VORTEX_CORE_API static ModuleLoader* loader();

	private:
		static ModuleLoader* _loader;
	};


	class DummyModuleLoader : public ModuleLoader {
	public:
		virtual Module* load_module(const std::string& module_name) override;
		virtual Module* get_module(const std::string& module_name) override;
		virtual bool module_loaded(const std::string& module_name) override;
	};


	struct ModuleInstance;


#ifdef WIN32

	class WindowsModuleLoader : public ModuleLoader {
	public:
		virtual ~WindowsModuleLoader();

		virtual Module* load_module(const std::string& module_name) override;
		virtual Module* get_module(const std::string& module_name) override;
		virtual bool module_loaded(const std::string& module_name) override;

	private:
		std::unordered_map<std::string, ModuleInstance*> _loaded_modules;
	};

#else

	class LinuxModuleLoader : public ModuleLoader {
	public:
		virtual ~LinuxModuleLoader();

		virtual Module* load_module(const std::string& module_name) override;
		virtual Module* get_module(const std::string& module_name) override;
		virtual bool module_loaded(const std::string& module_name) override;

	private:
		std::unordered_map<std::string, ModuleInstance*> _loaded_modules;
	};

#endif

}  // namespace Vortex::Core::Modules
