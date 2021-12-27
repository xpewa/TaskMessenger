#include "client.h"

#include <sstream>
#include <string_view>

#include <boost/thread/thread.hpp>

using boost::asio::ip::address;

constexpr std::string_view MESSAGE_END = "\r\n";
constexpr std::string_view IP_SERVER = "127.0.0.1";
constexpr size_t PORT_SERVER_TASK = 5050;
constexpr size_t PORT_SERVER_MESSAGE = 5051;

class Client
{
public:
  static User UserFromStr(const std::string &str);
  static std::vector<Message> MessagesFromStr(const std::string &str);
  static std::vector<Task> TasksFromStr(const std::string &str);
  static std::string Authorize(const std::string& name);
  static std::string GetMessageForTask(const Task& task);
  static std::string GetTaskForUser(const User& user);
  static std::string AddNewTask(const Task& task);
  static std::string EditTask(const Task& task);
  static std::string AddNewMessage(const Task& task, const Message& message);
};

User Client::UserFromStr(const std::string &str) {
    User res;

    std::string string(str);
    string.erase(str.find_last_not_of("\r\n") + 1);
    std::vector<std::string> strings;
    std::istringstream f(string);
    std::string s;
    while (getline(f, s, ':')) {
      strings.push_back(s);
    }

    res.setName(strings[0]);
    res.setId(std::stoi(strings[1]));

    return res;
}

std::vector<Message> Client::MessagesFromStr(const std::string &str) {
  std::vector<Message> res;

  std::string string(str);
  string.erase(str.find_last_not_of("\r\n") + 1);
  std::vector<std::string> strings;
  std::istringstream f(string);
  if (string[0] != 0) {
    std::string s;
    while (getline(f, s, ':')) {
      strings.push_back(s);
    }
    for (int i = 1; i < strings.size(); i += 2) {
      Message msg;
      msg.setText(strings[i]);
      User writer;
      writer.setName(strings[i + 1]);
      msg.setWriter(writer);

      res.push_back(msg);
    }
  }

  return res;
}

std::vector<Task> Client::TasksFromStr(const std::string &str) {
  std::vector<Task> tasks;

  std::string string(str);
  string.erase(str.find_last_not_of("\r\n") + 1);
  std::vector<std::string> strings;
  std::istringstream f(string);
  std::string s;
  while (getline(f, s, ':')) {
    strings.push_back(s);
  }


  for (int i = 1; i < strings.size(); i += 4) {
    Task task;
    task.setId(std::stoi(strings[i]));

    task.setTitle(strings[i+1]);

    User assigner;
    assigner.setName(strings[i+2]);
    task.setAssigner(assigner);

    User worker;
    worker.setName(strings[i+3]);
    task.setWorker(worker);

    int done;
    done = std::stoi(strings[i+4]);
    if (done) {
      task.setDone(true);
    }
    else {
      task.setDone(false);
    }

    tasks.push_back(task);
  }

  return tasks;
}

std::string Client::Authorize(const std::string& name) {
  std::string str = "authorization:" + name + "\r\n";
  return str;
}
std::string Client::GetMessageForTask(const Task& task) {
  std::string str = "get:" + std::to_string(task.getId()) + "\r\n";
  return str;
}
std::string Client::GetTaskForUser(const User& user) {
  std::string str = "get:" + user.getName() + "\r\n";
  return str;
}
std::string Client::AddNewTask(const Task& task) {
  std::string str = "add:" + task.getTitle() + ":" +
                  task.getAssigner().getName() + ":" +
                  task.getWorker().getName() + "\r\n";
  return str;
}
std::string Client::EditTask(const Task& task) {
  std::string done = "";
  if (task.getDone()) {
    done = "1";
  }
  else {
    done = "0";
  }
  std::string str = "edit:" + std::to_string(task.getId()) + ":" +
                    task.getTitle() + ":" +
                    task.getAssigner().getName() + ":" +
                    task.getWorker().getName() + ":" +
                    done + "\r\n";
  return str;
}
std::string Client::AddNewMessage(const Task& task, const Message& message) {
  std::string str = "add:" + message.getText() + ":" +
                    std::to_string(message.getWriter().getId()) + ":" +
                    std::to_string(task.getId()) + "\r\n";
  return str;
}


bool ClientBoostAsio::Connect() {
  tcp::endpoint ep1(address::from_string(std::string(IP_SERVER)), PORT_SERVER_TASK);
  tcp::endpoint ep2(address::from_string(std::string(IP_SERVER)), PORT_SERVER_MESSAGE);
  boost::system::error_code error;
  socket_task.connect(ep1, error);
  socket_message.connect(ep2, error);
  if (error) {
    return false;
  }
  open.store(true);

  return true;
}

std::string ClientBoostAsio::sendRequestGetAnswer(const std::string& request, tcp::socket& socket) {
  os << request;
  boost::asio::write(socket, write_buffer);

  boost::asio::read_until(socket, read_buffer, MESSAGE_END);
  std::string answer(std::istreambuf_iterator<char>(is), {});
  return answer;
}

User ClientBoostAsio::Authorize(const std::string& name) {
  auto request = Client::Authorize(name);

  return Client::UserFromStr(sendRequestGetAnswer(request, socket_task));
}
std::vector<Message> ClientBoostAsio::GetMessageForTask(const Task& task) {
  auto request = Client::GetMessageForTask(task);

  return Client::MessagesFromStr(sendRequestGetAnswer(request, socket_message));
}
std::vector<Task> ClientBoostAsio::GetTaskForUser(const User& user) {
  auto request = Client::GetTaskForUser(user);

  return Client::TasksFromStr(sendRequestGetAnswer(request, socket_task));
}
void ClientBoostAsio::AddNewTask(const Task& task) {
  auto request = Client::AddNewTask(task);

  os << request;
  boost::asio::write(socket_task, write_buffer);
}
void ClientBoostAsio::AddNewMessage(const Task& task, const Message& message) {
  auto request = Client::AddNewMessage(task, message);

  os << request;
  boost::asio::write(socket_message, write_buffer);
}

void ClientBoostAsio::EditTask(const Task& task) {
  auto request = Client::EditTask(task);

  os << request;
  boost::asio::write(socket_message, write_buffer);
}

void ClientBoostAsio::setPresenter(IPresenter* presenter_) { presenter = presenter_; }