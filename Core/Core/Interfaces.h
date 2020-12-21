#pragma once

#include <string>
#include <map>
#include <boost/beast/http.hpp>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core {

    class RuntimeInterface;


    class HostInterface {
    public:
        VORTEX_CORE_API inline HostInterface(RuntimeInterface* runtime) : _runtime(runtime) {}
        VORTEX_CORE_API virtual ~HostInterface() = default;

        VORTEX_CORE_API virtual void init(const std::string& hostname) = 0;

        VORTEX_CORE_API virtual std::string id() = 0;
        VORTEX_CORE_API virtual std::string hostname() = 0;
        VORTEX_CORE_API virtual std::string application_id() = 0;
        VORTEX_CORE_API virtual Maze::Element config() = 0;
        VORTEX_CORE_API virtual std::string script() = 0;
        VORTEX_CORE_API virtual std::string post_script() = 0;

    protected:
        RuntimeInterface* _runtime;
    };


    class ApplicationInterface {
    public:
        VORTEX_CORE_API inline ApplicationInterface(RuntimeInterface* runtime) : _runtime(runtime) {}
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

    protected:
        RuntimeInterface* _runtime;
    };


    class RouterInterface {
    public:
        VORTEX_CORE_API inline RouterInterface(RuntimeInterface* runtime) : _runtime(runtime) {}
        VORTEX_CORE_API virtual ~RouterInterface() = default;

        VORTEX_CORE_API virtual void init() = 0;

        VORTEX_CORE_API virtual std::string hostname() = 0;
        VORTEX_CORE_API virtual std::string lang() = 0;
        VORTEX_CORE_API virtual std::string controller() = 0;
        VORTEX_CORE_API virtual std::vector<std::string> args() = 0;

        VORTEX_CORE_API virtual std::string request_post_body() = 0;

        VORTEX_CORE_API virtual std::map<std::string, std::string> cookies() = 0;
        VORTEX_CORE_API virtual std::string cookie(const std::string& cookie_name, bool* out_cookie_exists = nullptr) = 0;

    protected:
        RuntimeInterface* _runtime;
    };


    class ControllerInterface {
    public:
        VORTEX_CORE_API inline ControllerInterface(RuntimeInterface* runtime) : _runtime(runtime) {}
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

    protected:
        RuntimeInterface* _runtime;
    };


    class ViewInterface {
    public:
        VORTEX_CORE_API inline ViewInterface(RuntimeInterface* runtime) : _runtime(runtime) {}
        VORTEX_CORE_API virtual ~ViewInterface() = default;

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

    protected:
        RuntimeInterface* _runtime;
    };


    class ScriptInterface {
    public:
        VORTEX_CORE_API inline ScriptInterface(RuntimeInterface* runtime) : _runtime(runtime) {}
        VORTEX_CORE_API virtual ~ScriptInterface() = default;

        VORTEX_CORE_API virtual void init() = 0;

        VORTEX_CORE_API virtual void exec(const std::string& script) = 0;

    protected:
        RuntimeInterface* _runtime;
    };


    class RuntimeInterface {
    public:
        VORTEX_CORE_API virtual ~RuntimeInterface() = default;

        VORTEX_CORE_API virtual void init() = 0;
        VORTEX_CORE_API virtual void run() = 0;
        VORTEX_CORE_API virtual void exit() = 0;

        VORTEX_CORE_API virtual const std::string& client_ip() const = 0;
        VORTEX_CORE_API virtual boost::beast::http::request<boost::beast::http::string_body>* request() = 0;
        VORTEX_CORE_API virtual boost::beast::http::response<boost::beast::http::string_body>* response() = 0;
        VORTEX_CORE_API virtual Maze::Element* config() = 0;
        VORTEX_CORE_API virtual RouterInterface* router() = 0;
        VORTEX_CORE_API virtual HostInterface* host() = 0;
        VORTEX_CORE_API virtual ApplicationInterface* application() = 0;
        VORTEX_CORE_API virtual ControllerInterface* controller() = 0;
        VORTEX_CORE_API virtual ViewInterface* view() = 0;
        VORTEX_CORE_API virtual ScriptInterface* script() = 0;
    };

}  // namespace Vortex::Core
