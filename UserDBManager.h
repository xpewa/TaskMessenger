#ifndef CPP_PROJECT_USERDBMANAGER_H
#define CPP_PROJECT_USERDBMANAGER_H

#include "IDBManager.h"


class UserDBManager : public IDBManager{
private:
    mysqlx::Session session = mysqlx::Session(HOST/*, PORT*/, USER_NAME, PWD, SCHEMA_NAME);
    mysqlx::Schema schema = session.getDefaultSchema();
    mysqlx::Table user = schema.getTable("user", true);
public:
    virtual bool update_user_data(User user);

    virtual User get_user(int id);

    virtual User search_user(string name_);

    virtual vector<User> get_all_users();

    virtual void drop() { session.sql("DROP TABLE user;").execute();}

    virtual bool add_task(Task task) { throw wrong_manager("Using UserDBManager for TaskDBManager function"); }

    virtual vector<Task> get_user_tasks(int id) { throw wrong_manager("Using UserDBManager for TaskDBManager function"); }

    virtual bool add_message(Message message) { throw wrong_manager("Using UserDBManager for MessageDBManager function"); }

    virtual vector<Message> get_messages(int task_id) { throw wrong_manager("Using UserDBManager for MessageDBManager function"); }
};


#endif //CPP_PROJECT_USERDBMANAGER_H
