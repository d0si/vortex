#pragma once

#include <string>
#include <map>
#include <boost/beast/http.hpp>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core::Modules {
    class DependencyInjector;
}

namespace Vortex::Core {

    typedef boost::beast::http::request<boost::beast::http::string_body> string_body_request;
    typedef boost::beast::http::response<boost::beast::http::string_body> string_body_response;

    class RequestInterface {
    public:
        VORTEX_CORE_API inline RequestInterface(const std::shared_ptr<string_body_request>& request)
            : _request(request) {}

        VORTEX_CORE_API virtual inline string_body_request& request() { return *_request; };
        VORTEX_CORE_API virtual inline const std::shared_ptr<string_body_request>& request_ptr() { return _request; };

    protected:
        std::shared_ptr<string_body_request> _request;
    };


    class ResponseInterface {
    public:
        VORTEX_CORE_API inline ResponseInterface(const std::shared_ptr<string_body_response>& response)
            : _response(response) {}

        VORTEX_CORE_API virtual inline string_body_response& response() { return *_response; };
        VORTEX_CORE_API virtual inline const std::shared_ptr<string_body_response>& response_ptr() { return _response; };

    protected:
        std::shared_ptr<string_body_response> _response;
    };


    class HostResolverInterface {
    public:
        VORTEX_CORE_API virtual ~HostResolverInterface() = default;

        VORTEX_CORE_API virtual void init(const std::string& hostname) = 0;

        VORTEX_CORE_API virtual std::string id() = 0;
        VORTEX_CORE_API virtual std::string hostname() = 0;
        VORTEX_CORE_API virtual std::string application_id() = 0;
        VORTEX_CORE_API virtual Maze::Element config() = 0;
        VORTEX_CORE_API virtual std::string script() = 0;
        VORTEX_CORE_API virtual std::string post_script() = 0;
    };


    class ApplicationInterface {
    public:
        VORTEX_CORE_API virtual ~ApplicationInterface() = default;

        VORTEX_CORE_API virtual void init(const std::string& application_id) = 0;

        VORTEX_CORE_API virtual std::string id() = 0;
        VORTEX_CORE_API virtual std::string title() = 0;
        VORTEX_CORE_API virtual Maze::Element config() = 0;
        VORTEX_CORE_API virtual std::string script() = 0;
        VORTEX_CORE_API virtual std::string post_script() = 0;

        VORTEX_CORE_API virtual Maze::Element find_object_in_application_storage(
            const std::string& collection, const Maze::Element& query,
            bool search_other_storages = true) = 0;
    };


    class RouterInterface {
    public:
        VORTEX_CORE_API virtual ~RouterInterface() = default;

        VORTEX_CORE_API virtual void init() = 0;

        VORTEX_CORE_API virtual std::string hostname() = 0;
        VORTEX_CORE_API virtual std::string lang() = 0;
        VORTEX_CORE_API virtual std::string controller() = 0;
        VORTEX_CORE_API virtual std::vector<std::string> args() = 0;

        VORTEX_CORE_API virtual std::string request_post_body() = 0;

        VORTEX_CORE_API virtual std::map<std::string, std::string> cookies() = 0;
        VORTEX_CORE_API virtual std::string cookie(const std::string& cookie_name, bool* out_cookie_exists = nullptr) = 0;
    };


    class ControllerInterface {
    public:
        VORTEX_CORE_API virtual ~ControllerInterface() = default;

        VORTEX_CORE_API virtual void init(const std::string& application_id,
            const std::string& name, const std::string& method) = 0;

        VORTEX_CORE_API virtual std::string id() = 0;
        VORTEX_CORE_API virtual std::string name() = 0;
        VORTEX_CORE_API virtual Maze::Element app_ids() = 0;
        VORTEX_CORE_API virtual std::string script() = 0;
        VORTEX_CORE_API virtual std::string post_script() = 0;
        VORTEX_CORE_API virtual std::string content_type() = 0;
        VORTEX_CORE_API virtual std::string method() = 0;
    };


    class ViewEngineInterface {
    public:
        VORTEX_CORE_API virtual ~ViewEngineInterface() = default;

        VORTEX_CORE_API virtual void output() = 0;
        VORTEX_CORE_API virtual void respond() = 0;

        VORTEX_CORE_API virtual void echo(const std::string& contents) = 0;
        VORTEX_CORE_API virtual void set_content_type(const std::string& content_type) = 0;
        VORTEX_CORE_API virtual void set_status_code(int status_code) = 0;
        VORTEX_CORE_API virtual void set_cookie(const std::string& cookie_name, const std::string& value, const std::string& params = "") = 0;
        VORTEX_CORE_API virtual void set_cookie(const std::string& cookie_string) = 0;

        VORTEX_CORE_API virtual void clear() = 0;
        VORTEX_CORE_API virtual void finish() = 0;
        VORTEX_CORE_API virtual std::string parse(const std::string& code) = 0;

        VORTEX_CORE_API virtual void set_template(const std::string& name) = 0;
        VORTEX_CORE_API virtual std::string parse_template() = 0;

        VORTEX_CORE_API virtual void set_page(const std::string& name) = 0;
        VORTEX_CORE_API virtual std::string parse_page() = 0;
    };


    class ScriptEngineInterface {
    public:
        VORTEX_CORE_API virtual ~ScriptEngineInterface() = default;

        VORTEX_CORE_API virtual void init() = 0;

        VORTEX_CORE_API virtual void exec(const std::string& script) = 0;
    };


    class RuntimeInterface {
    public:
        VORTEX_CORE_API virtual ~RuntimeInterface() = default;

        VORTEX_CORE_API virtual void init() = 0;
        VORTEX_CORE_API virtual void run() = 0;
        VORTEX_CORE_API virtual void exit() = 0;

        VORTEX_CORE_API virtual const std::string& client_ip() const = 0;
        VORTEX_CORE_API virtual Maze::Element* config() = 0;
        VORTEX_CORE_API virtual std::shared_ptr<RouterInterface> router() = 0;
        VORTEX_CORE_API virtual HostResolverInterface* host() = 0;
        VORTEX_CORE_API virtual ApplicationInterface* application() = 0;
        VORTEX_CORE_API virtual ControllerInterface* controller() = 0;
        VORTEX_CORE_API virtual ViewEngineInterface* view() = 0;
        VORTEX_CORE_API virtual ScriptEngineInterface* script() = 0;
    };

}  // namespace Vortex::Core
