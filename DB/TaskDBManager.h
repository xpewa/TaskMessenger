#ifndef CPP_PROJECT_TASKDBMANAGER_H
#define CPP_PROJECT_TASKDBMANAGER_H

#include "DBConnection.h"
#include "ITaskDBManager.h"


class TaskDBManager : public ITaskDBManager {
private:
    mysqlx::Session &session;
    mysqlx::Schema schema;
    mysqlx::Table task;
public:
    TaskDBManager(mysqlx::Session &session_) : session(session_), schema(session.getSchema("test", true)), task(schema.getTable("task", true)) {}

    bool add_task(const Task &task) override;

    std::vector<Task> get_user_tasks(int user_id) override;

    bool complete_task(int task_id) override;

    void drop() override { session.sql("DROP TABLE task;").execute(); }

//    bool add_message(const Message &message) override { throw wrong_manager("Using TaskDBManager for MessageDBManager function"); }
//
//    std::vector<Message> get_messages_for_task_id(int task_id) override { throw wrong_manager("Using TaskDBManager for MessageDBManager function"); }
//
//    bool add_user(const User &user) override { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }
//
//    User get_user(int id) override { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }
//
//    User search_user(std::string name_) override { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }
//
//    std::vector<User> get_all_users() override { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }
};


#endif //CPP_PROJECT_TASKDBMANAGER_H
