#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include "user.h"
#include "task.h"
#include "message.h"

namespace Ui {
class TaskDialog;
}

class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDialog(QWidget *parent = nullptr);
    ~TaskDialog();

    void setUser(const User& user_);
    void setTask(const Task& task_);
    void pushBackMessage(const Message& message_);
    void setMessages(const std::vector<Message>& messages_);
    User& getUser();
    Task& getTask();
    Message& getMessage();
    std::vector<Message>& getMessages();

    void updateTaskData(Task& task);
    void updateMessages();

private slots:
    void on_buttonSendMessage_clicked();
    void on_checkBox_stateChanged(int arg1);
    void addMessage(Message message);

signals:
    void onButtonSendMessage();
    void onCheckBox();
    void conn();

private:
    Ui::TaskDialog *ui;
    User user;
    Task task;
    Message message;
    std::vector<Message> messages;
};

#endif // TASKDIALOG_H
