#ifndef CPP_PROJECT_IDBMANAGER_H
#define CPP_PROJECT_IDBMANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>
#include <vector>

using namespace std;

const string HOST = "localhost";
const int PORT = 33060;
const string USER_NAME = "root";
const string PWD = "1111";
const string SCHEMA_NAME = "test";

//проверка на наличие БД и таблиц и их создание, если их нет
void CheckDB();

//исключение при использовании неправильного менеджера
class wrong_manager : public exception{
private:
    string errstr;
public:
    wrong_manager(string errstr_) : errstr(errstr_){}
    const char * what () const throw ()
    {
        return errstr.c_str();
    }
};

class User {
public:
    int id;
    string login;
    string username;
    string password;

    User(int id_, string login_, string username_ = "", string password_ = "") : id(id_), login(login_), username(username_), password(password_) {}

    User(string login_, string username_ = "", string password_ = "") : id(0), login(login_), username(username_), password(password_) {}
};

class Task {
public:
    int id;
    string head;
    string body;
    bool completion = false;
    int assigner_id;
    int executor_id;

    Task(int id_, string head_, string body_, bool completion_, int assigner_id_, int executor_id_)
            : id(id_), head(head_), body(body_), completion(completion_), assigner_id(assigner_id_), executor_id(executor_id_) {}

    Task(string head_, string body_, int assigner_id_, int executor_id_)
            : head(head_), body(body_), assigner_id(assigner_id_), executor_id(executor_id_) {}

    Task(string head_, string body_, int assigner_id_)
            : head(head_), body(body_), assigner_id(assigner_id_), executor_id(assigner_id_) {}

    Task(string head_, int assigner_id_, int executor_id_)
            : head(head_), assigner_id(assigner_id_), executor_id(executor_id_) {}
};

class Message {
public:
    Message(int id_, string text_, int task_id_, int from_id_)
            : id(id_), text(text_), task_id(task_id_), from_id(from_id_) {}

    Message(string text_, int task_id_, int from_id_)
            : text(text_), task_id(task_id_), from_id(from_id_) {}

    int id;
    string text;
    int task_id;
    int from_id;
};

class IDBManager {
public:
    virtual bool add_user(User user) = 0;

    virtual User get_user(int id) = 0;

    virtual User search_user(string name_) = 0;

    virtual vector<User> get_all_users() = 0;

    virtual bool add_task(Task task) = 0;

//    virtual bool task_done();

    virtual vector<Task> get_user_tasks(int id) = 0;

    virtual bool add_message(Message message) = 0;

    virtual vector<Message> get_messages(int task_id) = 0;

    virtual void drop() = 0;
};

#endif // CPP_PROJECT_IDBMANAGER_H
