#ifndef TASK_SERVER_H
#define TASK_SERVER_H

#include <sys/socket.h>
#include <string>
#include <vector>

class Task
{
public:
    int id;
    std::string head;
    std::string body;
    bool completion;
    int assigner_id;
    int executor_id;
};

class Task_Server
{
public:
    int ActiveSocket;
    int ListeningSocket;

    bool StartServer();
    bool StopServer();
    bool Login(int, std::string);
    void SendTaskToClient(Task);
    Task GetTaskFromClient();
    void SendBossReportToClient(std::string);
    void SendUserListToClient(std::vector<std::string>);
};

#endif TASK_SERVER_H