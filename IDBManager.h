#ifndef CPP_PROJECT_IDBMANAGER_H
#define CPP_PROJECT_IDBMANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>
#include <vector>
#define HOST "localhost"
#define PORT 33060
#define USER_NAME "root"
#define PWD "1111"
#define SCHEMA_NAME "test"

using namespace std;

void CheckDB();

class User {
public:
    int id;
    string login;

    User(int id_, string new_login) : id(id_), login(new_login) {}

    User(string new_login) : id(0), login(new_login) {}
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
};

class Message {
public:
    Message(int new_id, string new_text, int new_task_id, int new_from_id)
            : id(new_id), text(new_text), task_id(new_task_id), from_id(new_from_id) {}

    Message(string new_text, int new_task_id, int new_from_id)
            : text(new_text), task_id(new_task_id), from_id(new_from_id) {}

    int id;
    string text;
    int task_id;
    int from_id;
};

class IDBManager {
protected:
    mysqlx::Session session = mysqlx::Session(HOST, PORT, USER_NAME, PWD, SCHEMA_NAME);
    mysqlx::Schema schema = session.getDefaultSchema();
    mysqlx::Table user = schema.getTable("user", true);
public:
    bool update_user_data(User user);

    User get_user(int id);

    User search_user(string name_);

    virtual bool add_task(Task task) = 0;

    virtual vector<Task> get_user_tasks(int id) = 0;

    virtual bool add_message(Message message) = 0;

    virtual vector<Message> get_messages(int task_id) = 0;
};

#endif // CPP_PROJECT_IDBMANAGER_H
