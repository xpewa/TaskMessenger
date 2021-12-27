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
};


#endif //CPP_PROJECT_TASKDBMANAGER_H
