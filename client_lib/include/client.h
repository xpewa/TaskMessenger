#ifndef TASKMESSENGER_CLIENT_H
#define TASKMESSENGER_CLIENT_H

#include "IClient.h"

#include <boost/bind/bind.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>

using tcp = boost::asio::ip::tcp;
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace net = boost::asio;

class ClientBoostBeast : public IClient {
public:
  ClientBoostBeast() = default;
  ~ClientBoostBeast() = default;

  User Authorize(std::string name) override;
  std::vector<Message> GetMessageForTask(Task task) override;
  std::vector<Task> GetTaskForUser(User user) override;
  void AddNewTask(Task task) override;
  void AddNewMessage(Message message) override;
};

class Client : public std::enable_shared_from_this<Client>
{
public:
  Client(boost::asio::io_context& io_context)
      : resolver_(net::make_strand(io_context)),
        stream_(net::make_strand(io_context)) {}

  void run(const std::string& server, const std::string& port, const std::string& path);

private:
  void handle_resolve(beast::error_code err,
                      tcp::resolver::results_type results);

  void handle_connect(beast::error_code err, tcp::resolver::results_type::endpoint_type);

  void handle_write_request(beast::error_code err,
                            std::size_t bytes_transferred);

  void handle_read(beast::error_code err,
                   std::size_t bytes_transferred);

private:
  tcp::resolver resolver_;

  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;

  http::request<http::empty_body> request_;
  http::response<http::string_body> response_;
};

#endif // TASKMESSENGER_CLIENT_H
