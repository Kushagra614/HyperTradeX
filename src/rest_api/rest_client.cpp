#include "rest_client.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <exception>

namespace beast = boost::beast;
namespace asio = boost::asio;
namespace http = beast::http;
using namespace std;

    RestClient::RestClient(const string &host, const string &port)
        : host(host), port(port), io_context(), resolver(io_context), stream(io_context) {}

    // send GET Req
    string RestClient::send_get_request(const string &target)
    {
        try
        {
            // Resolve host and port
            auto const results = resolver.resolve(this-> host, this->port);
            beast::get_lowest_layer(this->stream).connect(results);
        
            //setup the request
            http::request<http::string_body> req{http::verb::get, target,11};
            req.set(http::field::host, this ->host);
            req.set(http::field::user_agent, "HyperTradeX");

            //Send the Request
            http::write(this->stream, req);

            //Receive the Response
            http::response<http::dynamic_body> res;
            beast::flat_buffer buffer;
            http::read(this->stream, buffer, res);

            //Return the response body as a string
            string res_body = beast::buffers_to_string(res.body().data());
            return res_body;

        }
        catch(const exception& e)
        {
            spdlog::error("Error: {}", e.what());
            return "";
        }

    }
