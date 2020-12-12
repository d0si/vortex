#include <Server/Http/HttpSession.h>
#include <iostream>
#include <boost/asio/bind_executor.hpp>
#include <boost/beast/http.hpp>
#include <Core/Framework.h>
#include <Core/Exceptions/VortexException.h>
#ifdef HAS_FEATURE_MONGO
#include <mongocxx/exception/exception.hpp>
#endif

namespace asio = boost::asio;
namespace beast = boost::beast;
using asio::ip::tcp;
using boost::system::error_code;

namespace Vortex::Server::Http {

    HttpSession::HttpSession(
        const Maze::Element& config,
        tcp::socket socket)
        : _config(config), _stream(std::move(socket)) {}

    void HttpSession::run() {
        do_read();
    }

    void HttpSession::do_read() {
        _req = {};

        _stream.expires_after(std::chrono::seconds(30));

        beast::http::async_read(_stream, _buffer, _req, beast::bind_front_handler(
            &HttpSession::on_read,
            shared_from_this()));
    }

    void HttpSession::on_read(error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec == beast::http::error::end_of_stream) {
            return do_close();
        }

        if (ec) {
            std::cout << "HttpSession read failed. " << ec.message() << std::endl;

            return;
        }

        const clock_t begin_time = clock();
        std::cout << "Request received ("
            << _req.method_string().to_string()
            << ") "
            << _req.target().to_string()
            << std::endl;

        _res.version(_req.version());

        _res.keep_alive(_req.keep_alive());
        if (_req.method() == boost::beast::http::verb::post) {
            _res.keep_alive(false);
        }

        _res.set(boost::beast::http::field::server, "Vortex Framework");
        _res.set(boost::beast::http::field::content_type, "text/html");
        _res.result(boost::beast::http::status::ok);

        Vortex::Core::Framework* framework = nullptr;

        try {
            framework = new Vortex::Core::Framework(
                _config,
                _stream.socket().remote_endpoint().address().to_string(),
                &_req,
                &_res);

            framework->setup();

            framework->run();
        }
        catch (int e) {
            e;
#ifdef HAS_FEATURE_MONGO
        }
        catch (mongocxx::exception e) {
            _res.result(boost::beast::http::status::internal_server_error);
            std::string what = e.what();
            _res.body() = "MongoDb exception: " + what;
#endif
        }
        catch (Core::Exceptions::VortexException e) {
            _res.result(boost::beast::http::status::internal_server_error);
            std::string what = e.what();
            _res.body() = "Exception - " + what;
        }
        catch (std::runtime_error e) {
            _res.result(boost::beast::http::status::internal_server_error);
            std::string what = e.what();
            _res.body() = "Runtime error: " + what;
        }
        catch (std::exception e) {
            _res.result(boost::beast::http::status::internal_server_error);
            std::string what = e.what();
            _res.body() = "Runtime error: " + what;
        }
        catch (...) {
            _res.result(boost::beast::http::status::internal_server_error);
            _res.body() = "Internal server error";
        }

        if (framework != nullptr) {
            delete framework;
        }

        _res.set(boost::beast::http::field::content_length, _res.body().size());

        std::cout << "Request finished "
            << _req.target().to_string()
            << " ["
            << std::to_string(float(clock() - begin_time) / CLOCKS_PER_SEC)
            << "]"
            << std::endl;

        send();
    }

    void HttpSession::on_write(
        bool close,
        error_code ec,
        std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec) {
            std::cout << "HttpSession write failed. " << ec.message() << std::endl;

            return;
        }

        if (close) {
            return do_close();
        }

        do_read();
    }

    void HttpSession::do_close() {
        error_code ec;

        _stream.socket().shutdown(tcp::socket::shutdown_send, ec);
    }

    void HttpSession::send() {
        beast::http::async_write(_stream, _res, beast::bind_front_handler(
            &HttpSession::on_write,
            shared_from_this(),
            _res.need_eof()));
    }

}
