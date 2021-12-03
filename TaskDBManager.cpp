#include "TaskDBManager.h"

bool TaskDBManager::add_task(Task task_) {
    try {
        task.insert("head", "body", "assigner_id", "executor_id").values(task_.head, task_.body, task_.assigner_id, task_.executor_id).execute();
    } catch (mysqlx::abi2::r0::Error){
        return false;
    }
    return true;
}

vector<Task> TaskDBManager::get_user_tasks(int id) {
    vector<Task> tasks;
    mysqlx::RowResult res = task.select("id", "head", "body", "completion", "assigner_id", "executor_id").where(
            "assigner_id = :id OR executor_id = :id").bind("id", id).execute();
    while (mysqlx::Row row = res.fetchOne()) {
        Task tmp(row[0].get<int>(), row[1].get<string>(), row[2].get<string>(), row[3].get<bool>(), row[4].get<int>(),
                 row[5].get<int>());
        tasks.push_back(tmp);
    }
    return tasks;
}