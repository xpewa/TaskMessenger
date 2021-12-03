#include <iostream>
#include "UserDBManager.h"
#include "TaskDBManager.h"
#include "MessageDBManager.h"

using namespace std;


int main() {
    CheckDB();

    UserDBManager user_manager;
    TaskDBManager task_manager;
    MessageDBManager message_manager;

    cout<<"Ввод пользователей..."<<endl;
    user_manager.update_user_data(User("AAA"));
    user_manager.update_user_data(User("BBB"));
    user_manager.update_user_data(User("CCC"));
    cout<<"Неверный ввод пользователей..."<<endl;
//    cout<<"Через другие менеджеры:"<<endl;
//    task_manager.update_user_data(User("ddd"));
//    message_manager.update_user_data(User("eee"));
//    cout<<"Занятый логин:"<<endl;
//    user_manager.update_user_data(User("AAA"));

    cout<<"Все пользователи"<<endl;
    for(int i=0; i < user_manager.get_all_users().size(); i++){
        cout << "\t" << user_manager.get_all_users()[i].login << endl;
    }

    cout<<"Поиск по id:"<<endl;
    cout << user_manager.get_user(3).id << ' ' << user_manager.get_user(3).login << endl;
    cout << user_manager.get_user(2).id << ' ' << user_manager.get_user(2).login << endl;
    cout << user_manager.get_user(1).id << ' ' << user_manager.get_user(1).login << endl;

    cout<<"Поиск по имени:"<<endl;
    cout << user_manager.search_user("CCC").id << ' ' << user_manager.search_user("CCC").login << endl;
    cout << user_manager.search_user("BBB").id << ' ' << user_manager.search_user("BBB").login << endl;
    cout << user_manager.search_user("AAA").id << ' ' << user_manager.search_user("AAA").login << endl;

    cout<<"Добавление задач..."<<endl;
    task_manager.add_task(Task("task1 from A to B", "task1 desc", 1, 2));
    task_manager.add_task(Task("task2 from A to C", "task2 desc", 1, 3));
    task_manager.add_task(Task("task3 from B to A", "task3 desc", 2, 1));

    cout << "Tasks for A: " << '(' << task_manager.get_user_tasks(1)[0].head << ')' << ' ' << '(' << task_manager.get_user_tasks(1)[1].head << ')' << ' ' << '(' << task_manager.get_user_tasks(1)[2].head << ')' << endl;
    cout << "Tasks for B: " << '(' << task_manager.get_user_tasks(2)[0].head << ')' << ' ' << '(' << task_manager.get_user_tasks(2)[1].head << ')' << endl;
    cout << "Tasks for C: " << '(' << task_manager.get_user_tasks(3)[0].head << ')' << endl;

    cout<<"Добавление сообщений..."<<endl;
    message_manager.add_message(Message("message in task1 from A", 1, 1));
    message_manager.add_message(Message("message in task1 from B", 1, 2));
    message_manager.add_message(Message("message in task2 from A", 2, 1));
    message_manager.add_message(Message("message in task2 from C", 2, 3));
    message_manager.add_message(Message("message in task3 from A", 3, 1));
    message_manager.add_message(Message("message in task3 from B", 3, 2));

    cout<<"Messages in task1:"<<endl;
    for(int i=0; i < message_manager.get_messages(1).size(); i++){
        cout << "\t" << message_manager.get_messages(1)[i].text << endl;
    }
    cout<<"Messages in task2:"<<endl;
    for(int i=0; i < message_manager.get_messages(2).size(); i++){
        cout << "\t" << message_manager.get_messages(2)[i].text << endl;
    }
    cout<<"Messages in task3:"<<endl;
    for(int i=0; i < message_manager.get_messages(3).size(); i++){
        cout << "\t" << message_manager.get_messages(3)[i].text << endl;
    }

    message_manager.drop();
    task_manager.drop();
    user_manager.drop();
}
