#include "MessageDBManager.h"

bool MessageDBManager::add_message(Message message_) {
    message.insert("text", "task_id", "from_id").values(message_.text, message_.task_id, message_.from_id).execute();
}

vector<Message> MessageDBManager::get_messages(int task_id) {
    vector<Message> messages;
    mysqlx::RowResult res = message.select("id", "text", "from_id").where("task_id = :id").bind("id",
                                                                                                task_id).execute();
    while (mysqlx::Row row = res.fetchOne()) {
        Message tmp(row[0].get<int>(), row[1].get<string>(), task_id, row[2].get<int>());
        messages.push_back(tmp);
    }
    return messages;
}
