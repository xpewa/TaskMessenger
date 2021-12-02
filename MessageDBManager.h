#ifndef CPP_PROJECT_MESSAGEDBMANAGER_H
#define CPP_PROJECT_MESSAGEDBMANAGER_H

#include "IDBManager.h"


class MessageDBManager : public IDBManager {
private:
    mysqlx::Table message = schema.getTable("message", true);
public:
    virtual bool add_message(Message message);

    virtual vector<Message> get_messages(int task_id);

    virtual bool add_task(Task task) { throw invalid_argument("Using MessageDBManager for TaskDBManager function"); }

    virtual vector<Task> get_user_tasks(int id) { throw invalid_argument("Using MessageDBManager for TaskDBManager function"); };
};


#endif //CPP_PROJECT_MESSAGEDBMANAGER_H
