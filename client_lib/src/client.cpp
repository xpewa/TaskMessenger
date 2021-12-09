#include "client.h"

#include <sstream>
#include <string_view>

#include <boost/thread/thread.hpp>

using boost::asio::ip::address;

constexpr std::string_view MESSAGE_END = "\n\r\n\r";
constexpr std::string_view IP_SERVER = "127.0.0.1";
constexpr size_t PORT_SERVER_TASK = 5050;
constexpr size_t PORT_SERVER_MESSAGE = 80;

class Client
{
public:
  static User UserFromStr(std::string const &str);
  static std::vector<Message> MessagesFromStr(std::string const &str);
  static std::vector<Task> TasksFromStr(std::string const &str);
  static std::string Disconnect();
  static std::string Authorize(std::string &name);
  static std::string GetMessageForTask(Task task);
  static std::string GetTaskForUser(User user);
  static std::string AddNewTask(Task task);
  static std::string AddNewMessage(Message message);
};

User Client::UserFromStr(std::string const &str) {
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

std::vector<Message> Client::MessagesFromStr(std::string const &str) {
  std::vector<Message> res;

  std::string string(str);
  string.erase(str.find_last_not_of("\r\n") + 1);
  std::vector<std::string> strings;
  std::istringstream f(string);
  std::string s;
  while (getline(f, s, ':')) {
    strings.push_back(s);
  }

  int count = std::stoi(strings[0]);
  for (int i = 1; i < count; i += 3) {
    Message msg;
    msg.setText(strings[i]);
    User writer;
    writer.setName(strings[i+1]);
    msg.setWriter(writer);

    res.push_back(msg);
  }

  return res;
}

std::vector<Task> Client::TasksFromStr(std::string const &str) {
  std::vector<Task> tasks;

  std::string string(str);
  string.erase(str.find_last_not_of("\r\n") + 1);
  std::vector<std::string> strings;
  std::istringstream f(string);
  std::string s;
  while (getline(f, s, ':')) {
    strings.push_back(s);
  }

  int count = std::stoi(strings[0]);
  for (int i = 1; i < count; i += 4) {
    Task task;
    task.setId(std::stoi(strings[i]));

    task.setTitle(strings[i+1]);

    User assigner;
    assigner.setName(strings[i+2]);
    task.setAssigner(assigner);

    User worker;
    worker.setName(strings[i+3]);
    task.setWorker(worker);

    tasks.push_back(task);
  }

  return tasks;
}

std::string Client::Disconnect() {
  return "";
}
std::string Client::Authorize(std::string &name) {
  std::string str = "authorization:" + name + "\r\n";
  return str;
}
std::string Client::GetMessageForTask(Task task) {
  std::string str = "get:" + std::to_string(task.getId()) + "\r\n";
  return str;
}
std::string Client::GetTaskForUser(User user) {
  std::string str = "get:" + user.getName() + "\r\n";
  return str;
}
std::string Client::AddNewTask(Task task) {
  std::string str = "add:" + task.getTitle() + ":" +
                  task.getAssigner().getName() + ":" +
                  task.getWorker().getName() + "\r\n";
  return str;
}
std::string Client::AddNewMessage(Message message) {
  std::string str = "add:" + message.getText() + ":" +
                    message.getWriter().getName() + "\r\n";
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
bool ClientBoostAsio::Disconnect() {
  auto request = Client::Disconnect();
  os << request;
  boost::asio::write(socket_task, write_buffer);
  os << request;
  boost::asio::write(socket_message, write_buffer);
  open.store(false);

  return true;
}
void ClientBoostAsio::Run() {
  while ( open.load() ) {
    if (answers.empty()) {}
    }
  socket_task.close();
  socket_message.close();
}

std::string ClientBoostAsio::getAnswer() {
  while (answers.empty()) {
    boost::this_thread::sleep(boost::posix_time::microseconds(100));
  }

  std::string res = answers.front();
  answers.pop();
  return res;
}

std::string ClientBoostAsio::sendRequestGetAnswer(std::string request, tcp::socket& socket) {
  os << request;
  boost::asio::write(socket, write_buffer);

  boost::asio::read_until(socket, read_buffer, MESSAGE_END);
  std::string answer(std::istreambuf_iterator<char>(is), {});
  return answer;
}

User ClientBoostAsio::Authorize(std::string name) {
  auto request = Client::Authorize(name);

  return Client::UserFromStr(sendRequestGetAnswer(request, socket_task));
}
std::vector<Message> ClientBoostAsio::GetMessageForTask(Task task) {
  auto request = Client::GetMessageForTask(task);

  return Client::MessagesFromStr(sendRequestGetAnswer(request, socket_message));
}
std::vector<Task> ClientBoostAsio::GetTaskForUser(User user) {
  auto request = Client::GetTaskForUser(user);

  return Client::TasksFromStr(sendRequestGetAnswer(request, socket_task));
}
void ClientBoostAsio::AddNewTask(Task task) {
  auto request = Client::AddNewTask(task);

  os << request;
  boost::asio::write(socket_task, write_buffer);
}
void ClientBoostAsio::AddNewMessage(Message message) {
  auto request = Client::AddNewMessage(message);

  os << request;
  boost::asio::write(socket_message, write_buffer);
}