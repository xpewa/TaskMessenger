#include "client.h"

#include <sstream>
#include <string_view>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/thread/thread.hpp>

namespace pt = boost::property_tree;

using boost::asio::ip::address;

constexpr std::string_view MESSAGE_END = "\n\r\n\r";
constexpr std::string_view IP_SERVER = "127.0.0.1";
constexpr size_t PORT_SERVER_TASK = 80;
constexpr size_t PORT_SERVER_MESSAGE = 80;

class Client
{
  static std::string StrFromPtree(boost::property_tree::ptree const &request);
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

std::string Client::StrFromPtree(boost::property_tree::ptree const &request) {
  std::stringstream json;
  pt::write_json(json, request);
  return json.str() + "\n\r\n\r";
}
User Client::UserFromStr(std::string const &str) {
    boost::property_tree::ptree ptree;
    pt::read_json(str, ptree);

    User res;
    res.setId(ptree.get<int>("id"));
    res.setName(ptree.get<std::string>("name"));
    return res;
}
std::vector<Message> Client::MessagesFromStr(std::string const &str) {}
std::vector<Task> Client::TasksFromStr(std::string const &str) {}

std::string Client::Disconnect() {
  pt::ptree request;

  request.put("command", "disconnect");

  return StrFromPtree(request);
}
std::string Client::Authorize(std::string &name) {
  pt::ptree param;
  pt::ptree request;

  param.put("name", name);

  request.put("command", "authorization");
  request.add_child("parameters", param);

  return StrFromPtree(request);
}
std::string Client::GetMessageForTask(Task task) {}
std::string Client::GetTaskForUser(User user) {}
std::string Client::AddNewTask(Task task) {}
std::string Client::AddNewMessage(Message message) {}


bool ClientBoostAsio::Connect() {
  tcp::endpoint ep1(address::from_string(std::string(IP_SERVER)), PORT_SERVER_TASK);
  boost::system::error_code error;
  socket.connect(ep1, error);
  if (error) {
    return false;
  }
  open.store(true);

  return true;
}
bool ClientBoostAsio::Disconnect() {
  auto request = Client::Disconnect();
  requests.push(request);
  open.store(false);

  return true;
}
void ClientBoostAsio::Run() {
  while ( open.load() ) {
    if (requests.empty()) {
      continue;
    }

    os << requests.front();
    requests.pop();

    boost::asio::write(socket, write_buffer);

    boost::asio::read_until(socket, read_buffer, MESSAGE_END);
    std::string answer(std::istreambuf_iterator<char>(is), {});
    answers.push(answer);
    }

  socket.close();
}

std::string ClientBoostAsio::getAnswer() {
  while (answers.empty()) {
    boost::this_thread::sleep(boost::posix_time::microseconds(100));
  }

  std::string res = answers.front();
  answers.pop();
  return res;
}

User ClientBoostAsio::Authorize(std::string name) {
  auto request = Client::Authorize(name);
  requests.push(request);

  std::string answer = getAnswer();
  User user = Client::UserFromStr(answer);
  return user;
}
std::vector<Message> ClientBoostAsio::GetMessageForTask(Task task) {}
std::vector<Task> ClientBoostAsio::GetTaskForUser(User user) {}
void ClientBoostAsio::AddNewTask(Task task) {}
void ClientBoostAsio::AddNewMessage(Message message) {}