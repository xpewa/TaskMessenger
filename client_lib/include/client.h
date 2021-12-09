#ifndef TASKMESSENGER_CLIENT_H
#define TASKMESSENGER_CLIENT_H

#include "IClient.h"
#include "tsqueue.h"

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::tcp;
using boost::asio::io_context;

class ClientBoostAsio : public IClient {
public:
  ClientBoostAsio() : socket_task(context), socket_message(context), is(&read_buffer), os(&write_buffer) {};
  ~ClientBoostAsio() { socket_task.close(); socket_message.close(); }

  bool Connect();
  bool Disconnect();
  void Run();

  User Authorize(std::string name) override;
  std::vector<Message> GetMessageForTask(Task task) override;
  std::vector<Task> GetTaskForUser(User user) override;
  void AddNewTask(Task task) override;
  void AddNewMessage(Message message) override;

private:
  std::string getAnswer();
  std::string sendRequestGetAnswer(std::string request, tcp::socket& socket);

  io_context context;
  tcp::socket socket_task;
  tcp::socket socket_message;

  std::ostream os;
  std::istream is;
  boost::asio::streambuf write_buffer;
  boost::asio::streambuf read_buffer;

  TSQueue<std::string> answers;

  std::atomic<bool> open;
};

#endif // TASKMESSENGER_CLIENT_H
