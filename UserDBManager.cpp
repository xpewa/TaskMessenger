#include "UserDBManager.h"

bool UserDBManager::update_user_data(User user_) {
    try{
        user.insert("login").values(user_.login).execute();
    } catch (mysqlx::abi2::r0::Error) {
        return false;
    }
    return true;
}

User UserDBManager::get_user(int id) {
    string res = user.select("login").where("id = :id").bind("id", id).execute().fetchOne()[0].get<string>();
    return User(id, res);
}

User UserDBManager::search_user(string name_) {
    mysqlx::Row row = user.select("id", "login").where("login = :login").bind("login", name_).execute().fetchOne();
    int id = row[0].get<int>();
    string name = row[1].get<string>();
    return User(id, name);
}

vector<User> UserDBManager::get_all_users(){
    vector<User> users;
    mysqlx::RowResult res = user.select("id", "login").execute();
    while (mysqlx::Row row = res.fetchOne()) {
        User tmp(row[0].get<int>(), row[1].get<string>());
        users.push_back(tmp);
    }
    return users;
}
