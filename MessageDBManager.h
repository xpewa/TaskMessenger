#ifndef CPP_PROJECT_MESSAGEDBMANAGER_H
#define CPP_PROJECT_MESSAGEDBMANAGER_H

#include "IDBManager.h"


class MessageDBManager : public IDBManager {
private:
    mysqlx::Session session = mysqlx::Session(HOST/*, PORT*/, USER_NAME, PWD, SCHEMA_NAME);
    mysqlx::Schema schema = session.getDefaultSchema();
    mysqlx::Table message = schema.getTable("message", true);
public:
    virtual bool add_message(Message message);

    virtual vector<Message> get_messages(int task_id);

    virtual void drop() { session.sql("DROP TABLE message;").execute();}

    virtual bool add_task(Task task) { throw wrong_manager("Using MessageDBManager for TaskDBManager function"); }

    virtual vector<Task> get_user_tasks(int id) { throw wrong_manager("Using MessageDBManager for TaskDBManager function"); };

    virtual bool update_user_data(User user) { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }

    virtual User get_user(int id) { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }

    virtual User search_user(string name_) { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }

    virtual vector<User> get_all_users() { throw wrong_manager("Using MessageDBManager for UserDBManager function"); }
};


#endif //CPP_PROJECT_MESSAGEDBMANAGER_H
