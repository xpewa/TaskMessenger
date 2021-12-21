#ifndef TASKMANAGER_DB_TABLES_H
#define TASKMANAGER_DB_TABLES_H

#include <iostream>

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


#endif //TASKMANAGER_DB_TABLES_H
