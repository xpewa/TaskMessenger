#ifndef TASKMANAGER_DB_ITASKDBMANAGER_H
#define TASKMANAGER_DB_ITASKDBMANAGER_H

#include <vector>
#include "tables.h"


class ITaskDBManager {
public:
//    virtual ~ITaskDBManager() = 0;

    virtual bool add_task(const Task& task) = 0;

//    virtual bool task_done();

    virtual std::vector<Task> get_user_tasks(int id) = 0;

    virtual void drop() = 0;
};


#endif //TASKMANAGER_DB_ITASKDBMANAGER_H
