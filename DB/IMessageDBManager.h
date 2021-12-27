#ifndef TASKMANAGER_DB_IMESSAGEDBMANAGER_H
#define TASKMANAGER_DB_IMESSAGEDBMANAGER_H

#include <vector>
#include "tables.h"

//интерфейс для менеджера сообщений в БД
class IMessageDBManager {
public:
//добавление сообщения в БД
    virtual bool add_message(const Message &message) = 0;

//получение сообщений
    virtual std::vector<Message> get_messages_for_task_id(int task_id) = 0;

//сброс таблицы (системное)
    virtual void drop() = 0;
};


#endif //TASKMANAGER_DB_IMESSAGEDBMANAGER_H
