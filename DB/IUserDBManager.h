#ifndef TASKMANAGER_DB_IUSERDBMANAGER_H
#define TASKMANAGER_DB_IUSERDBMANAGER_H

#include <vector>
#include "tables.h"

//интерфейс для менеджера пользователей в БД
class IUserDBManager {
public:
//добавление пользователя в БД
    virtual bool add_user(const User &user) = 0;

//получение пользователя по id
    virtual User get_user(int id) = 0;

//получение пользователя по логину
    virtual User search_user(std::string login_) = 0;

//получение всех пользователей
    virtual std::vector<User> get_all_users() = 0;

//сброс таблицы (системное)
    virtual void drop() = 0;
};


#endif //TASKMANAGER_DB_IUSERDBMANAGER_H
