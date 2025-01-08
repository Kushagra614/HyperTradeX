#ifndef rest_client_h
#define rest_client_h

#include <string>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <exception>

using namespace std;
namespace beast = boost::beast;
namespace asio = boost::asio;
namespace http = beast::http;

class RestClient
{

private:
    string host;
    string port;
    asio::io_context io_context;
    asio::ip::tcp::resolver resolver;
    beast::tcp_stream stream;

public:
    // ctor
    RestClient(const string &host, const string &port);

    // Send GET Request
    string send_get_request(const string &target);
};

#endif