#ifndef CPP_PROJECT_MESSAGEDBMANAGER_H
#define CPP_PROJECT_MESSAGEDBMANAGER_H

#include "Connection.h"
#include "IMessageDBManager.h"


class MessageDBManager : public IMessageDBManager {
private:
    mysqlx::Session &session;
    mysqlx::Schema schema;
    mysqlx::Table message;
public:
    MessageDBManager(mysqlx::Session &session_) : session(session_), schema(session.getSchema("test", true)), message(schema.getTable("message", true)) {}

    bool add_message(const Message &message) override;

    std::vector<Message> get_messages_for_task_id(int task_id) override;

    void drop() override { session.sql("DROP TABLE message;").execute(); }

//    bool add_task(const Task &task) override { throw wrong_manager("Using MessageDBManager for TaskDBManager function"); }
//
//    std::vector<Task> get_user_tasks(int id) override { throw wrong_manager("Using MessageDBManager for TaskDBManager function"); };
//
//    bool add_user(const User &user) override { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }
//
//    User get_user(int id) override { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }
//
//    User search_user(std::string name_) override { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }
//
//    std::vector<User> get_all_users() override { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }
};


#endif //CPP_PROJECT_MESSAGEDBMANAGER_H
