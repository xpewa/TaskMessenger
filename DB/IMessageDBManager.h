#ifndef TASKMANAGER_DB_IMESSAGEDBMANAGER_H
#define TASKMANAGER_DB_IMESSAGEDBMANAGER_H

#include <vector>
#include "tables.h"

class IMessageDBManager {
public:
//    virtual ~IMessageDBManager() = 0;

    virtual bool add_message(const Message& message) = 0;

    virtual std::vector<Message> get_messages_for_task_id(int task_id) = 0;

    virtual void drop() = 0;
};


#endif //TASKMANAGER_DB_IMESSAGEDBMANAGER_H
