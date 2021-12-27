#include "DBConnection.h"

//установление соединения, создание БД если нет
DBConnection::DBConnection() : session(mysqlx::Session(HOST/*, PORT*/, USER_NAME, PWD)), schema(session.createSchema("test", true)) {
    session.sql("USE test;").execute();
    session.sql("CREATE TABLE IF NOT EXISTS user (id INT PRIMARY KEY AUTO_INCREMENT, login VARCHAR(20) UNIQUE, username VARCHAR(30), password VARCHAR(30));").execute();
    session.sql(
            "CREATE TABLE IF NOT EXISTS task (id INT PRIMARY KEY AUTO_INCREMENT, head VARCHAR(100) NOT NULL, body VARCHAR(2500), completion BOOL DEFAULT 0, assigner_id INT NOT NULL, FOREIGN KEY (assigner_id) REFERENCES user(id), executor_id INT NOT NULL, FOREIGN KEY (executor_id) REFERENCES user(id));").execute();
    session.sql(
            "CREATE TABLE IF NOT EXISTS message (id INT PRIMARY KEY AUTO_INCREMENT, text VARCHAR(100) NOT NULL, task_id INT NOT NULL, FOREIGN KEY (task_id) REFERENCES task(id), from_id INT NOT NULL, FOREIGN KEY (from_id) REFERENCES user(id));").execute();
}

