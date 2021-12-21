#include "Connection.h"
//#include <algorithm>
//#include <iostream>


//mysqlx::Table createTable(mysqlx::Session &session, const wstring &name, const wstring &command) {
//    wstring quoted_name = L"`"
//                          + wstring(session.getDefaultSchemaName())
//                          + L"`.`" + wstring(name) + L"`";
//    session.sql(L"DROP TABLE IF EXISTS" + quoted_name).execute();
//
//    wstring create = L"CREATE TABLE ";
//    create += quoted_name;
//    create += command;
//
//    session.sql(create).execute();
//    return session.getDefaultSchema().getTable(name);
//}

//IUserDBManager::IUserDBManager(){
//    vector<string> tablenames = schema.getTableNames();
//    if (find(tablenames.begin(), tablenames.end(), "user") == tablenames.end()) {
//        user = createTable(session, L"test",
//                           L"(id INT PRIMARY KEY AUTO_INCREMENT, login VARCHAR(20));");
//        task = createTable(session, L"test",
//                           L"(id INT PRIMARY KEY AUTO_INCREMENT, head VARCHAR(100) NOT NULL, body VARCHAR(500), completion BOOL DEFAULT 0, assigner_id INT NOT NULL, FOREIGN KEY (assigner_id) REFERENCES user(id), executor_id INT NOT NULL, FOREIGN KEY (executor_id) REFERENCES user(id));");
//        message = createTable(session, L"test",
//                              L"(id INT PRIMARY KEY AUTO_INCREMENT, text VARCHAR(100) NOT NULL, task_id INT NOT NULL, FOREIGN KEY (task_id) REFERENCES task(id), from_id INT NOT NULL, FOREIGN KEY (from_id) REFERENCES user(id));");
//
//    }
//}


//User IUserDBManager::add_user() {
//    return
//}


Connection::Connection() : session(mysqlx::Session(HOST/*, PORT*/, USER_NAME, PWD)), schema(session.createSchema("test", true)){
    session.sql("USE test;").execute();
    session.sql("CREATE TABLE IF NOT EXISTS user (id INT PRIMARY KEY AUTO_INCREMENT, login VARCHAR(20) UNIQUE, username VARCHAR(30), password VARCHAR(30));").execute();
    session.sql("CREATE TABLE IF NOT EXISTS task (id INT PRIMARY KEY AUTO_INCREMENT, head VARCHAR(100) NOT NULL, body VARCHAR(2500), completion BOOL DEFAULT 0, assigner_id INT NOT NULL, FOREIGN KEY (assigner_id) REFERENCES user(id), executor_id INT NOT NULL, FOREIGN KEY (executor_id) REFERENCES user(id));").execute();
    session.sql("CREATE TABLE IF NOT EXISTS message (id INT PRIMARY KEY AUTO_INCREMENT, text VARCHAR(100) NOT NULL, task_id INT NOT NULL, FOREIGN KEY (task_id) REFERENCES task(id), from_id INT NOT NULL, FOREIGN KEY (from_id) REFERENCES user(id));").execute();
}


//bool IUserDBManager::add_user(User user_) {
//    user.insert("login").values(user_.login).execute();
//}
//
//User IUserDBManager::get_user(int id) {
//    string res = user.select("login").where("id = :id").bind("id", id).execute().fetchOne()[0].get<string>();
//    return User(id, res);
//}
//
//User IUserDBManager::search_user(string name_) {
//    mysqlx::Row row = user.select("id", "login").where("login = :login").bind("login", name_).execute().fetchOne();
//    int id = row[0].get<int>();
//    string name = row[1].get<string>();
//    return User(id, name);
//}
//
//vector<User> IUserDBManager::get_all_users(){
//    vector<User> users;
//    mysqlx::RowResult res = user.select("id", "login").execute();
//    while (mysqlx::Row row = res.fetchOne()) {
//        User tmp(row[0].get<int>(), row[1].get<string>());
//        users.push_back(tmp);
//    }
//    return users;
//}


//bool IUserDBManager::add_task(Task task_) {
//    task.insert("head", "body", "assigner_id", "executor_id").values(task_.head, task_.body, task_.assigner_id,
//                                                                     task_.executor_id).execute();
//}
//
//vector<Task> IUserDBManager::get_user_tasks(int id) {
//    vector<Task> tasks;
//    mysqlx::RowResult res = task.select("id", "head", "body", "completion", "assigner_id", "executor_id").where(
//            "assigner_id = :id OR executor_id = :id").bind("id", id).execute();
//    while (mysqlx::Row row = res.fetchOne()) {
//        Task tmp(row[0].get<int>(), row[1].get<string>(), row[2].get<string>(), row[3].get<bool>(), row[4].get<int>(),
//                 row[5].get<int>());
//        tasks.push_back(tmp);
//    }
//    return tasks;
//}
//
//bool IUserDBManager::add_message(Message message_) {
//    message.insert("text", "task_id", "from_id").values(message_.text, message_.task_id, message_.from_id).execute();
//}
//
//vector<Message> IUserDBManager::get_messages_for_task_id(int task_id) {
//    vector<Message> messages;
//    mysqlx::RowResult res = message.select("id", "text", "from_id").where("task_id = :id").bind("id",
//                                                                                                task_id).execute();
//    while (mysqlx::Row row = res.fetchOne()) {
//        Message tmp(row[0].get<int>(), row[1].get<string>(), task_id, row[2].get<int>());
//        messages.push_back(tmp);
//    }
//    return messages;
//}
