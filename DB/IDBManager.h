#ifndef CPP_PROJECT_IDBMANAGER_H
#define CPP_PROJECT_IDBMANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>
#include <vector>
#include "tables.h"

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

class IDBManager {
public:
//    virtual ~IDBManager() = 0;

    virtual bool add_user(const User& user) = 0;

    virtual User get_user(int id) = 0;

    virtual User search_user(std::string name_) = 0;

    virtual std::vector<User> get_all_users() = 0;

    virtual bool add_task(const Task& task) = 0;

//    virtual bool task_done();

    virtual std::vector<Task> get_user_tasks(int id) = 0;

    virtual bool add_message(const Message& message) = 0;

    virtual std::vector<Message> get_messages_for_task_id(int task_id) = 0;

    virtual void drop() = 0;
};

#endif // CPP_PROJECT_IDBMANAGER_H
