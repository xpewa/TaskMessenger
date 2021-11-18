//
// Created by ivan on 18.11.2021.
//

#ifndef CPP_PROJECT_DATABASEMANAGER_H
#define CPP_PROJECT_DATABASEMANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>
#include <vector>

using namespace std;

class User {
public:
    int id;
    string login = "";

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

//    Task(int new_assigner_id): assigner_id(new_assigner_id){}
    Task(int id_, string head_, string body_, bool completion_, int assigner_id_, int executor_id_) : id(id_),
                                                                                                      head(head_),
                                                                                                      body(body_),
                                                                                                      completion(
                                                                                                              completion_),
                                                                                                      assigner_id(
                                                                                                              assigner_id_),
                                                                                                      executor_id(
                                                                                                              executor_id_) {}

    Task(string head_, string body_, int assigner_id_, int executor_id_) : head(head_), body(body_),
                                                                           assigner_id(assigner_id_),
                                                                           executor_id(executor_id_) {}
};

class Message {
public:
    Message(int new_id, string new_text, int new_task_id, int new_from_id) : id(new_id), text(new_text),
                                                                             task_id(new_task_id),
                                                                             from_id(new_from_id) {}

    Message(string new_text, int new_task_id, int new_from_id) : text(new_text),
                                                                 task_id(new_task_id),
                                                                 from_id(new_from_id) {}

    int id;
    string text;
    int task_id;
    int from_id;
};


class DatabaseManager {
private:
    string host = "localhost";
    int port = 33060;
    string user_name = "root";
    string password = "1111";
    string schema_name = "test";
    mysqlx::Session session = mysqlx::Session(host, port, user_name, password, schema_name);
    mysqlx::Schema schema = session.getDefaultSchema();
    mysqlx::Table user = schema.getTable("user", true);
    mysqlx::Table task = schema.getTable("task", true);
    mysqlx::Table message = schema.getTable("message", true);
public:
//    DatabaseManager();

//    bool create_tables();
//    User add_user();
    bool update_user_data(User user);

    User get_user(int id);

    User search_user(string name_);

    bool add_task(Task task);

    vector<Task> get_user_tasks(int id);

    bool add_message(Message message);

    vector<Message> get_messages(int task_id);


};


#endif //CPP_PROJECT_DATABASEMANAGER_H
