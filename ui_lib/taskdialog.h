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
    void setMessage(const Message& message_);
    void setMessages(const std::vector<Message>& messages_);
    User& getUser();
    Task& getTask();
    Message& getMessage();
    std::vector<Message>& getMessages();

    void updateTaskData(const Task& task);
    void updateMessages(const std::vector<Message>& message);

private slots:
    void on_buttonSendMessage_clicked();

signals:
    void onButtonSendMessage();

private:
    Ui::TaskDialog *ui;
    User user;
    Task task;
    Message message;
    std::vector<Message> messages;
};

#endif // TASKDIALOG_H
