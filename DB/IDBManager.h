#ifndef CPP_PROJECT_IDBMANAGER_H
#define CPP_PROJECT_IDBMANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>
#include <vector>

//using namespace std;

const std::string HOST = "localhost";
const int PORT = 33060;
const std::string USER_NAME = "root";
const std::string PWD = "1111";
const std::string SCHEMA_NAME = "test";

//установка соединения
class Connection {
public:
//    bool res = true;
    mysqlx::Session session = mysqlx::Session(HOST, PORT, USER_NAME, PWD);
//    session.sql("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = 'test'")
    mysqlx::Schema schema = session.createSchema("test", true);

    Connection();
};

//исключение при использовании неправильного менеджера
//class wrong_manager : public exception {
//private:
//    std::string errstr;
//public:
//    wrong_manager(std::string errstr_) : errstr(errstr_) {}
//
//    const char *what() const throw() {
//        return errstr.c_str();
//    }
//};

class wrong_manager : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class User {
public:
    int id;
    std::string login;
    std::string username;
    std::string password;

    User(int id_, std::string login_, std::string username_ = "", std::string password_ = "") : id(id_), login(login_), username(username_), password(password_) {}

    User(std::string login_, std::string username_ = "", std::string password_ = "") : id(0), login(login_), username(username_), password(password_) {}
};

class Task {
public:
    int id;
    std::string head;
    std::string body;
    bool completion = false;
    int assigner_id;
    int executor_id;

    Task(int id_, std::string head_, std::string body_, bool completion_, int assigner_id_, int executor_id_)
            : id(id_), head(head_), body(body_), completion(completion_), assigner_id(assigner_id_), executor_id(executor_id_) {}

    Task(std::string head_, std::string body_, int assigner_id_, int executor_id_)
            : head(head_), body(body_), assigner_id(assigner_id_), executor_id(executor_id_) {}

    Task(std::string head_, std::string body_, int assigner_id_)
            : head(head_), body(body_), assigner_id(assigner_id_), executor_id(/*assigner_id_*/1) {}

    Task(std::string head_, int assigner_id_, int executor_id_)
            : head(head_), assigner_id(assigner_id_), executor_id(executor_id_) {}
};

class Message {
public:
    Message(int id_, std::string text_, int task_id_, int from_id_)
            : id(id_), text(text_), task_id(task_id_), from_id(from_id_) {}

    Message(std::string text_, int task_id_, int from_id_)
            : text(text_), task_id(task_id_), from_id(from_id_) {}

    int id;
    std::string text;
    int task_id;
    int from_id;
};

class IDBManager {
public:
    virtual bool add_user(const User& user) = 0;

    virtual User get_user(int id) = 0;

    virtual User search_user(std::string name_) = 0;

    virtual std::vector<User> get_all_users() = 0;

    virtual bool add_task(const Task& task) = 0;

//    virtual bool task_done();

    virtual std::vector<Task> get_user_tasks(int id) = 0;

    virtual bool add_message(const Message& message) = 0;

    virtual std::vector<Message> get_messages(int task_id) = 0;

    virtual void drop() = 0;
};

#endif // CPP_PROJECT_IDBMANAGER_H
