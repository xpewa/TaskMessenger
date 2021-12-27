#ifndef CPP_PROJECT_USERDBMANAGER_H
#define CPP_PROJECT_USERDBMANAGER_H

#include "DBConnection.h"
#include "IUserDBManager.h"


class UserDBManager : public IUserDBManager {
private:
    mysqlx::Session &session;
    mysqlx::Schema schema;
    mysqlx::Table user;
public:
    UserDBManager(mysqlx::Session &session_) : session(session_), schema(session.getSchema("test", true)), user(schema.getTable("user", true)) {}

    bool add_user(const User &user) override;

    User get_user(int id) override;

    User search_user(std::string login_) override;

    std::vector<User> get_all_users() override;

    void drop() override { session.sql("DROP TABLE user;").execute(); }
};


#endif //CPP_PROJECT_USERDBMANAGER_H
