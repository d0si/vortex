#include <string>
#include <Core/Modules/Module.h>

namespace Vortex::App::Db {

    class DbAppModule : public Vortex::Core::Modules::Module {
    public:
        static const std::string s_module_name;

        virtual const std::string module_name() const override;

        virtual const std::vector<std::string> plugin_names() override;
        virtual Vortex::Core::Modules::Plugin* plugin(const std::string& plugin_name) override;

        virtual void register_di(const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di) override;
    };

}  // namespace Vortex::App::Db