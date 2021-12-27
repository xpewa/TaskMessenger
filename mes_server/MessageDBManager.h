#ifndef CPP_PROJECT_MESSAGEDBMANAGER_H
#define CPP_PROJECT_MESSAGEDBMANAGER_H

#include "DBConnection.h"
#include "IMessageDBManager.h"

//класс для взаимодействия с таблицей сообщений
class MessageDBManager : public IMessageDBManager {
private:
    mysqlx::Session &session;
    mysqlx::Schema schema;
    mysqlx::Table message;
    mysqlx::Table task;
public:
    MessageDBManager(mysqlx::Session &session_) : session(session_), schema(session.getSchema("test", true)), message(schema.getTable("message", true)), task(schema.getTable("task", true)) {}

    bool add_message(const Message &message) override;

    std::vector<Message> get_messages_for_task_id(int task_id) override;

    void drop() override { session.sql("DROP TABLE message;").execute(); }

    std::vector<int> get_users_for_task(int task_id);
};


#endif //CPP_PROJECT_MESSAGEDBMANAGER_H
