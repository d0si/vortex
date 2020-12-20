#include <Core/Applications/Application.hpp>
#include <Core/Modules/DependencyInjection.hpp>
#include <Core/GlobalRuntime.hpp>

#ifndef FALLBACK_VORTEX_HOST_ID
#define FALLBACK_VORTEX_HOST_ID "5fdceeb02a7af2799c4efd2d"
#endif

#ifndef FALLBACK_VORTEX_APPLICATION_ID
#define FALLBACK_VORTEX_APPLICATION_ID "5fdcee7369e2f923a3406417"
#endif

namespace Vortex::Core::Applications {

    IApplicationResolver::IApplicationResolver(
        const std::shared_ptr<Modules::DependencyInjector>& di,
        const std::shared_ptr<string_body_request>& request,
        const std::shared_ptr<string_body_response>& response,
        const Maze::Element& config)
        : _di(di), _request(request), _response(response), _config(config) {}


    BaseApplicationResolver::BaseApplicationResolver(
        const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
        const std::shared_ptr<string_body_request>& request,
        const std::shared_ptr<string_body_response>& response,
        const Maze::Element& config)
        : IApplicationResolver(di, request, response, config) {}

    std::shared_ptr<IApplicationRuntime> BaseApplicationResolver::get_application_runtime() {
        const std::string hostname = _request->base()[boost::beast::http::field::host].to_string();

        Maze::Element host_info = find_host_info(hostname);

        Maze::Element app_info = find_application_info(host_info.get("app_id").get_string());


        // if (app_info.get("_id").get("$oid").get_string() == "default_app_name"...
        return _di->activate_application_runtime(_request, _response, host_info, app_info, _config);
    }

    Maze::Element BaseApplicationResolver::find_host_info(const std::string& hostname) {
        std::string hostname_cache_key = "vortex.host.value.hostname." + hostname;
        Maze::Element host;
        if (GlobalRuntime::instance().cache().exists(hostname_cache_key)) {
            host = Maze::Element::from_json(GlobalRuntime::instance().cache().get(hostname_cache_key));
        }

        if (!host.has_children()) {
            host = GlobalRuntime::instance().storage().get_backend()
                ->simple_find_first("vortex", "hosts", Maze::Element({ "hostname" }, { hostname }).to_json(0));

            if (host.has_children()) {
                GlobalRuntime::instance().cache().set(hostname_cache_key, host.to_json(0));
            }
        }

        if (!host.has_children()) {
            host = Maze::Element(Maze::Type::Object);
            host.set("_id", Maze::Element({ "$oid" }, { Maze::Element(FALLBACK_VORTEX_HOST_ID) }));
            host.set("app_id", FALLBACK_VORTEX_APPLICATION_ID);
            host.set("hostname", hostname);
        }

        return host;
    }

    Maze::Element BaseApplicationResolver::find_application_info(const std::string& identifier) {
        std::string application_cache_key = "vortex.app.value.id." + identifier;
        Maze::Element app;
        if (GlobalRuntime::instance().cache().exists(application_cache_key)) {
            app = Maze::Element::from_json(GlobalRuntime::instance().cache().get(application_cache_key));
        }

        if (!app.has_children()) {
            app = GlobalRuntime::instance().storage().get_backend()
                ->simple_find_first("vortex", "apps", Maze::Element({ "_id" }, { Maze::Element({ "$oid" }, { identifier }) }).to_json());

            if (app.has_children()) {
                GlobalRuntime::instance().cache().set(application_cache_key, app.to_json(0));
            }
        }

        if (!app.has_children()) {
            app = Maze::Element(Maze::Type::Object);
            app.set("_id", Maze::Element({ "$oid" }, { Maze::Element(identifier) }));
        }

        return app;
    }


    IApplicationRuntime::IApplicationRuntime(
        const std::shared_ptr<Modules::DependencyInjector>& di,
        const std::shared_ptr<string_body_request>& request,
        const std::shared_ptr<string_body_response>& response,
        const Maze::Element& host_info,
        const Maze::Element& app_info,
        const Maze::Element& config)
        : _di(di), _request(request), _response(response), _host_info(host_info), _app_info(app_info), _config(config) {}

}
