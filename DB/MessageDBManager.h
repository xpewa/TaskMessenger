#ifndef CPP_PROJECT_MESSAGEDBMANAGER_H
#define CPP_PROJECT_MESSAGEDBMANAGER_H

#include "IDBManager.h"


class MessageDBManager : public IDBManager {
private:
    mysqlx::Session& session;
    mysqlx::Schema schema;
    mysqlx::Table message;
public:
    MessageDBManager(mysqlx::Session& session_) : session(session_), schema(session.getSchema("test", true)), message(schema.getTable("user", true)) {}

    virtual bool add_message(Message message);

    virtual vector<Message> get_messages(int task_id);

    virtual void drop() { session.sql("DROP TABLE message;").execute();}

    virtual bool add_task(Task task) { throw wrong_manager("Using MessageDBManager for TaskDBManager function"); }

    virtual vector<Task> get_user_tasks(int id) { throw wrong_manager("Using MessageDBManager for TaskDBManager function"); };

    virtual bool add_user(User user) { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }

    virtual User get_user(int id) { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }

    virtual User search_user(string name_) { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }

    virtual vector<User> get_all_users() { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }
};


#endif //CPP_PROJECT_MESSAGEDBMANAGER_H