#include "UserDBManager.h"

bool UserDBManager::add_user(User user_) {
    try{
        user.insert("login", "username", "password").values(user_.login, user_.username, user_.password).execute();
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
    mysqlx::RowResult res = user.select("id", "login").orderBy("id").execute();
    while (mysqlx::Row row = res.fetchOne()) {
        User tmp(row[0].get<int>(), row[1].get<string>());
        users.push_back(tmp);
    }
    return users;
}