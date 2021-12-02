#ifndef CPP_PROJECT_TASKDBMANAGER_H
#define CPP_PROJECT_TASKDBMANAGER_H

#include "IDBManager.h"


class TaskDBManager : public IDBManager {
private:
    mysqlx::Table task = schema.getTable("task", true);
public:
    virtual bool add_task(Task task);

    virtual vector<Task> get_user_tasks(int id);

    virtual bool add_message(Message message) { throw invalid_argument("Using TaskDBManager for MessageDBManager function"); }

    virtual vector<Message> get_messages(int task_id) { throw invalid_argument("Using TaskDBManager for MessageDBManager function"); };
};


#endif //CPP_PROJECT_TASKDBMANAGER_H
