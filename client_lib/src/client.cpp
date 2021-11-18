#include "client.h"

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

User ClientBoostBeast::Authorize(std::string name) {}
std::vector<Message> ClientBoostBeast::GetMessageForTask(Task task) {}
std::vector<Task> ClientBoostBeast::GetTaskForUser(User user) {}
void ClientBoostBeast::AddNewTask(Task task) {}
void ClientBoostBeast::AddNewMessage(Message message) {}