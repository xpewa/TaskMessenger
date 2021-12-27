#ifndef CPP_PROJECT_IDBMANAGER_H
#define CPP_PROJECT_IDBMANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>
#include <vector>
#include "tables.h"


const std::string HOST = "localhost";
const int PORT = 33060;
const std::string USER_NAME = "root";
const std::string PWD = "1111";
const std::string SCHEMA_NAME = "test";

//установка соединения
class DBConnection {
public:
//    bool res = true;
    mysqlx::Session session /*= mysqlx::Session(HOST*//*, PORT*//*, USER_NAME, PWD)*/;
    mysqlx::Schema schema /*= session.createSchema("test", true)*/;

    DBConnection();
};

class DB_except : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

//class IUserDBManager {
//public:
////    virtual ~IUserDBManager() = 0;
//
//    virtual bool add_user(const User& user) = 0;
//
//    virtual User get_user(int id) = 0;
//
//    virtual User search_user(std::string name_) = 0;
//
//    virtual std::vector<User> get_all_users() = 0;
//
//    virtual void drop() = 0;
//};

//class ITaskDBManager {
//public:
////    virtual ~ITaskDBManager() = 0;
//
//    virtual bool add_task(const Task& task) = 0;
//
////    virtual bool task_done();
//
//    virtual std::vector<Task> get_user_tasks(int id) = 0;
//
//    virtual void drop() = 0;
//};

//class IMessageDBManager {
//public:
////    virtual ~IMessageDBManager() = 0;
//
//    virtual bool add_message(const Message& message) = 0;
//
//    virtual std::vector<Message> get_messages_for_task_id(int task_id) = 0;
//
//    virtual void drop() = 0;
//};

#endif // CPP_PROJECT_IDBMANAGER_H
