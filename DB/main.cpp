#include <iostream>
#include "UserDBManager.h"
#include "TaskDBManager.h"
#include "MessageDBManager.h"

using namespace std;



void premade(UserDBManager& user_manager, TaskDBManager& task_manager, MessageDBManager& message_manager){
    cout<<"Ввод пользователей..."<<endl;
    user_manager.add_user(User("AAA"));
    user_manager.add_user(User("BBB"));
    user_manager.add_user(User("CCC"));
    cout<<"Неверный ввод пользователей..."<<endl;

//    cout<<"Через другие менеджеры:"<<endl;
//    task_manager.add_user(User("ddd"));
//    message_manager.add_user(User("eee"));
//    cout<<"Занятый логин:"<<endl;
//    user_manager.add_user(User("AAA"));

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

    for(int i=1; i<=user_manager.get_all_users().size(); i++){
        cout<<"Tasks for user "<<user_manager.get_user(i).login<<":\n";
        for(int j=0; j<task_manager.get_user_tasks(i).size(); j++){
            cout<<'\t'<<task_manager.get_user_tasks(i)[j].head<<endl;
        }
    }

    cout<<"Добавление сообщений..."<<endl;
    message_manager.add_message(Message("message in task1 from A", 1, 1));
    message_manager.add_message(Message("message in task1 from B", 1, 2));
    message_manager.add_message(Message("message in task2 from A", 2, 1));
    message_manager.add_message(Message("message in task2 from C", 2, 3));
    message_manager.add_message(Message("message in task3 from A", 3, 1));
    message_manager.add_message(Message("message in task3 from B", 3, 2));

    for(int i=0; i<task_manager.get_user_tasks(1).size(); i++){
        cout<<"Messages in task "<<task_manager.get_user_tasks(1)[i].head<<":\n";
        for(int j=0; j< message_manager.get_messages_for_task_id(i + 1).size(); j++){
            cout << '\t' << message_manager.get_messages_for_task_id(i + 1)[j].text << endl;
        }
    }
}

void show(UserDBManager& user_manager, TaskDBManager& task_manager, MessageDBManager& message_manager){
    cout<<"Все пользователи"<<endl;
    for(int i=0; i < user_manager.get_all_users().size(); i++){
        cout << "\t" << user_manager.get_all_users()[i].login << endl;
    }
    cout<<"------------------------------------------------\n";
    for(int i=1; i<=user_manager.get_all_users().size(); i++){
        cout<<"Tasks for user "<<user_manager.get_user(i).login<<":\n";
        for(int j=0; j<task_manager.get_user_tasks(i).size(); j++){
            cout<<'\t'<<task_manager.get_user_tasks(i)[j].head<<endl;
        }
    }
    cout<<"------------------------------------------------\n";

//    cout << "Tasks for A: " << '(' << task_manager.get_user_tasks(1)[0].head << ')' << ' ' << '(' << task_manager.get_user_tasks(1)[1].head << ')' << ' ' << '(' << task_manager.get_user_tasks(1)[2].head << ')' << endl;
//    cout << "Tasks for B: " << '(' << task_manager.get_user_tasks(2)[0].head << ')' << ' ' << '(' << task_manager.get_user_tasks(2)[1].head << ')' << endl;
//    cout << "Tasks for C: " << '(' << task_manager.get_user_tasks(3)[0].head << ')' << endl;

    for(int i=0; i<task_manager.get_user_tasks(1).size(); i++){
        cout<<"Messages in task "<<task_manager.get_user_tasks(1)[i].head<<":\n";
        for(int j=0; j< message_manager.get_messages_for_task_id(i + 1).size(); j++){
            cout << '\t' << message_manager.get_messages_for_task_id(i + 1)[j].text << endl;
        }
    }

//    cout<<"Messages in task1:"<<endl;
//    for(int i=0; i < message_manager.get_messages_for_task_id(1).size(); i++){
//        cout << "\t" << message_manager.get_messages_for_task_id(1)[i].text << endl;
//    }
//    cout<<"Messages in task2:"<<endl;
//    for(int i=0; i < message_manager.get_messages_for_task_id(2).size(); i++){
//        cout << "\t" << message_manager.get_messages_for_task_id(2)[i].text << endl;
//    }
//    cout<<"Messages in task3:"<<endl;
//    for(int i=0; i < message_manager.get_messages_for_task_id(3).size(); i++){
//        cout << "\t" << message_manager.get_messages_for_task_id(3)[i].text << endl;
//    }
}

void manual(UserDBManager& user_manager, TaskDBManager& task_manager, MessageDBManager& message_manager){
    int n_users = 0;
    vector<string> users;
    vector<string> task_heads;
    while(true){
        cout<<"Input login for new user:\t";
        string name;
        cin>>name;
        user_manager.add_user(User(name));
        n_users++;
        users.push_back(name);
        cout<<"More? (y/[n])\n";
        char more = 'n';
        cin>>more;
        if(more != 'y') break;
    }
    for(int i=0; i<n_users; i++){
        while(true){
            cout<<"Create task for user "<<users[i]<<"? (y/[n])\n";
            char more;
            cin>>more;
            if(more != 'y') break;
            cout<<"Input task head for user "<<users[i]<<":\t";
            string head;
            cin>>head;
            task_heads.push_back(head);
            cout<<"Input task body for user "<<users[i]<<":\t";
            string body;
            cin>>body;
            task_manager.add_task(Task(head, body, i+1));
        }
    }
    for(int i=0; i<n_users; i++){
        while(true){
            cout<<"Create message from user "<<users[i]<<"? (y/[n])\n";
            char more;
            cin>>more;
            if(more != 'y') break;
            cout<<"Choose task:\n";
            for(int j=0; j<task_manager.get_user_tasks(i+1).size(); j++)
                cout<<j+1<<'\t'<<task_manager.get_user_tasks(i+1)[j].head<<endl;
            int task_n;
            cin>>task_n;
            cout<<"Input message from user "<<users[i]<<" in task "<<task_manager.get_user_tasks(i+1)[task_n-1].head<<":\t";
            string mess;
            cin>>mess;
            message_manager.add_message(Message(mess, task_manager.get_user_tasks(i+1)[task_n-1].id, i+1));
        }
    }
    show(user_manager, task_manager, message_manager);

}

int main() {
    Connection connection;
    UserDBManager user_manager(connection.session);
    TaskDBManager task_manager(connection.session);
    MessageDBManager message_manager(connection.session);
    int choice;
    cout<<"1 - premade\n2 - manual\n";
    cin>>choice;
    switch (choice) {
        case 1:
            premade(user_manager, task_manager, message_manager);
            break;
        case 2:
            manual(user_manager, task_manager, message_manager);
            break;
    }

    message_manager.drop();
    task_manager.drop();
    user_manager.drop();

}
