#ifndef CPP_PROJECT_USERDBMANAGER_H
#define CPP_PROJECT_USERDBMANAGER_H

#include "IDBManager.h"


class UserDBManager : public IDBManager{
private:
    mysqlx::Session& session;
    mysqlx::Schema schema;
    mysqlx::Table user;
public:
    UserDBManager(mysqlx::Session& session_) : session(session_), schema(session.getSchema("test", true)), user(schema.getTable("user", true)) {}

    virtual bool add_user(const User& user);

    virtual User get_user(int id);

    virtual User search_user(std::string name_);

    virtual std::vector<User> get_all_users();

    virtual void drop() { session.sql("DROP TABLE user;").execute();}

    virtual bool add_task(const Task& task) { throw wrong_manager("Using UserDBManager for TaskDBManager function"); }

    virtual std::vector<Task> get_user_tasks(int id) { throw wrong_manager("Using UserDBManager for TaskDBManager function"); }

    virtual bool add_message(const Message& message) { throw wrong_manager("Using UserDBManager for MessageDBManager function"); }

    virtual std::vector<Message> get_messages(int task_id) { throw wrong_manager("Using UserDBManager for MessageDBManager function"); }
};


#endif //CPP_PROJECT_USERDBMANAGER_H
