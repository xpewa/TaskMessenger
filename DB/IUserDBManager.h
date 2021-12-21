#ifndef TASKMANAGER_DB_IUSERDBMANAGER_H
#define TASKMANAGER_DB_IUSERDBMANAGER_H

#include <vector>
#include "tables.h"

class IUserDBManager {
public:
//    virtual ~IUserDBManager() = 0;

    virtual bool add_user(const User& user) = 0;

    virtual User get_user(int id) = 0;

    virtual User search_user(std::string name_) = 0;

    virtual std::vector<User> get_all_users() = 0;

    virtual void drop() = 0;
};


#endif //TASKMANAGER_DB_IUSERDBMANAGER_H
