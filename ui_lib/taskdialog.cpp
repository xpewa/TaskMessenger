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
void TaskDialog::setMessages(const std::vector<Message>& messages_)
{
  messages = messages_;
}

void TaskDialog::on_buttonSendMessage_clicked()
{
  Message message;
  emit onButtonSendMessage(message);
}
