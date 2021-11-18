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

#endif // TASKMESSENGER_CLIENT_H
