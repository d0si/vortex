#include <Core/Applications/Application.hpp>

namespace Vortex::Core::Applications {

    IApplicationResolver::IApplicationResolver(
        const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
        const std::shared_ptr<string_body_request>& request,
        const std::shared_ptr<string_body_response>& response)
        : _di(di), _request(request), _response(response) {}

}
