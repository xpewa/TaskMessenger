#include "TaskDBManager.h"

bool TaskDBManager::add_task(const Task &task_) {
    try {
        task.insert("head", "body", "assigner_id", "executor_id").values(task_.head, task_.body, task_.assigner_id, task_.executor_id).execute();
    } catch (mysqlx::abi2::r0::Error) {
        return false;
    }
    return true;
}

std::vector<Task> TaskDBManager::get_user_tasks(int user_id) {
    std::vector<Task> tasks;
    mysqlx::RowResult res = task.select("id", "head", "body", "completion", "assigner_id", "executor_id").where(
                                                    "assigner_id = :user_id OR executor_id = :user_id").orderBy("id").bind("user_id", user_id).execute();
    while (mysqlx::Row row = res.fetchOne()) {
        Task tmp(row[0].get<int>(), row[1].get<std::string>(), row[2].get<std::string>(), row[3].get<bool>(), row[4].get<int>(),
                 row[5].get<int>());
        tasks.push_back(tmp);
    }
    return tasks;
}

bool TaskDBManager::complete_task(int task_id){
//    try{
        task.update().set("completion", 1).where("id = :task_id").bind("task_id", task_id).execute();
//    }
//    catch(){
//        return false;
//    }
    return true;
}