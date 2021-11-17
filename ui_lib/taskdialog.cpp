#include "taskdialog.h"
#include "ui_taskdialog.h"

TaskDialog::TaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskDialog)
{
    ui->setupUi(this);
}

TaskDialog::~TaskDialog()
{
    delete ui;
}

void TaskDialog::setUser(const User& user_)
{
  user = user_;
}
void TaskDialog::setTask(const Task& task_)
{
  task = task_;
}
void TaskDialog::setMessage(const Message& message_)
{
  message = message_;
}
void TaskDialog::setMessages(const std::vector<Message>& messages_)
{
  messages = messages_;
}
User& TaskDialog::getUser()
{
  return user;
}
Task& TaskDialog::getTask()
{
  return task;
}
Message& TaskDialog::getMessage()
{
  return message;
}
std::vector<Message>& TaskDialog::getMessages()
{
  return messages;
}

void TaskDialog::updateTaskData(const Task& task) {}
void TaskDialog::updateMessages(const std::vector<Message>& message) {}

void TaskDialog::on_buttonSendMessage_clicked()
{
  Message new_message;
  message = new_message;
  emit onButtonSendMessage();
}
