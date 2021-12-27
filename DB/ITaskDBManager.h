#ifndef TASKMANAGER_DB_ITASKDBMANAGER_H
#define TASKMANAGER_DB_ITASKDBMANAGER_H

#include <vector>
#include "tables.h"

//интерфейс для менеджера задач в БД
class ITaskDBManager {
public:
//добавление задачи в БД
    virtual bool add_task(const Task &task) = 0;

//установка флага "выполнено" для задачи
    virtual bool complete_task(int task_id) = 0;
//установка флага "не выполнено" для задачи
    virtual bool incomplete_task(int task_id) = 0;

//получение всех задач
    virtual std::vector<Task> get_user_tasks(int id) = 0;

//сброс таблицы (системное)
    virtual void drop() = 0;
};


#endif //TASKMANAGER_DB_ITASKDBMANAGER_H
