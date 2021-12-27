#include "MessageDBManager.h"

bool MessageDBManager::add_message(const Message& message_) {
    try{
        message.insert("text", "task_id", "from_id").values(message_.text, message_.task_id, message_.from_id).execute();
    } catch (mysqlx::abi2::r0::Error) {
        return false;
    }
    return true;
}

std::vector<Message> MessageDBManager::get_messages_for_task_id(int task_id) {
    std::vector<Message> messages;
    mysqlx::RowResult res = message.select("id", "text", "from_id").where("task_id = :id").orderBy("id").bind("id",task_id).execute();
    while (mysqlx::Row row = res.fetchOne()) {
        Message tmp(row[0].get<int>(), row[1].get<std::string>(), task_id, row[2].get<int>());
        messages.push_back(tmp);
    }
    return messages;
}
