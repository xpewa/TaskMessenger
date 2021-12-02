#include <iostream>
#include "TaskDBManager.h"
#include "MessageDBManager.h"

using namespace std;


int main() {
    CheckDB();

    TaskDBManager manager1;
    manager1.update_user_data(User("AAA"));
    manager1.update_user_data(User("BBB"));
    manager1.update_user_data(User("CCC"));
    cout<<"Поиск по id:"<<endl;
    cout<<manager1.get_user(3).id<<' '<<manager1.get_user(3).login<<endl;
    cout<<manager1.get_user(2).id<<' '<<manager1.get_user(2).login<<endl;
    cout<<manager1.get_user(1).id<<' '<<manager1.get_user(1).login<<endl;
    cout<<"Поиск по имени:"<<endl;
    cout<<manager1.search_user("CCC").id<<' '<<manager1.search_user("CCC").login<<endl;
    cout<<manager1.search_user("BBB").id<<' '<<manager1.search_user("BBB").login<<endl;
    cout<<manager1.search_user("AAA").id<<' '<<manager1.search_user("AAA").login<<endl;
    manager1.add_task(Task("task1 from A to B", "task1 desc", 1, 2));
    manager1.add_task(Task("task2 from A to C", "task2 desc", 1, 3));
    manager1.add_task(Task("task3 from B to A", "task3 desc", 2, 1));
    cout<<"Tasks for A: "<<'('<<manager1.get_user_tasks(1)[0].head<<')'<<' '<<'('<<manager1.get_user_tasks(1)[1].head<<')'<<' '<<'('<<manager1.get_user_tasks(1)[2].head<<')'<<endl;
    cout<<"Tasks for B: "<<'('<<manager1.get_user_tasks(2)[0].head<<')'<<' '<<'('<<manager1.get_user_tasks(2)[1].head<<')'<<endl;
    cout<<"Tasks for C: "<<'('<<manager1.get_user_tasks(3)[0].head<<')'<<endl;

    MessageDBManager manager2;
    manager2.add_message(Message("message in task1 from A", 1, 1));
    manager2.add_message(Message("message in task1 from B", 1, 2));
    manager2.add_message(Message("message in task2 from A", 2, 1));
    manager2.add_message(Message("message in task2 from C", 2, 3));
    manager2.add_message(Message("message in task3 from A", 3, 1));
    manager2.add_message(Message("message in task3 from B", 3, 2));
    cout<<"Messages in task1:"<<endl;
    for(int i=0; i<manager2.get_messages(1).size(); i++){
        cout<<"\t"<<manager2.get_messages(1)[i].text<< endl;
    }
    cout<<"Messages in task2:"<<endl;
    for(int i=0; i<manager2.get_messages(2).size(); i++){
        cout<<"\t"<<manager2.get_messages(2)[i].text<< endl;
    }
    cout<<"Messages in task3:"<<endl;
    for(int i=0; i<manager2.get_messages(3).size(); i++){
        cout<<"\t"<<manager2.get_messages(3)[i].text<< endl;
    }
}
