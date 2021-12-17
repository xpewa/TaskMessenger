#ifndef CPP_PROJECT_TASKDBMANAGER_H
#define CPP_PROJECT_TASKDBMANAGER_H

#include "IDBManager.h"


class TaskDBManager : public IDBManager {
private:
    mysqlx::Session& session;
    mysqlx::Schema schema;
    mysqlx::Table task;
public:
    TaskDBManager(mysqlx::Session& session_) : session(session_), schema(session.getSchema("test", true)), task(schema.getTable("task", true)) {}

    virtual bool add_task(Task task);

    virtual vector<Task> get_user_tasks(int id);

    virtual void drop() { session.sql("DROP TABLE task;").execute(); }

    virtual bool add_message(Message message) { throw wrong_manager("Using TaskDBManager for MessageDBManager function"); }

    virtual vector<Message> get_messages(int task_id) { throw wrong_manager("Using TaskDBManager for MessageDBManager function"); }

    virtual bool add_user(User user) { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }

    virtual User get_user(int id) { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }

    virtual User search_user(string name_) { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }

    virtual vector<User> get_all_users() { throw wrong_manager("Using TaskDBManager for UserDBManager function"); }
};


#endif //CPP_PROJECT_TASKDBMANAGER_H
