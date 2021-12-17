#ifndef CPP_PROJECT_USERDBMANAGER_H
#define CPP_PROJECT_USERDBMANAGER_H

#include "IDBManager.h"


class UserDBManager : public IUserDBManager {
private:
    mysqlx::Session &session;
    mysqlx::Schema schema;
    mysqlx::Table user;
public:
    UserDBManager(mysqlx::Session &session_) : session(session_), schema(session.getSchema("test", true)), user(schema.getTable("user", true)) {}

//     ~UserDBManager();

    bool add_user(const User &user) override;

    User get_user(int id) override;

    User search_user(std::string name_) override;

    std::vector<User> get_all_users() override;

    void drop() override { session.sql("DROP TABLE user;").execute(); }

//    bool add_task(const Task &task) override { throw wrong_manager("Using UserDBManager for TaskDBManager function"); }
//
//    std::vector<Task> get_user_tasks(int id) override { throw wrong_manager("Using UserDBManager for TaskDBManager function"); }
//
//    bool add_message(const Message &message) override { throw wrong_manager("Using UserDBManager for MessageDBManager function"); }
//
//    std::vector<Message> get_messages_for_task_id(int task_id) override { throw wrong_manager("Using UserDBManager for MessageDBManager function"); }
};


#endif //CPP_PROJECT_USERDBMANAGER_H
