#include "taskcreatedialog.h"
#include "ui_taskcreatedialog.h"

TaskCreateDialog::TaskCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskCreateDialog)
{
    ui->setupUi(this);
}

TaskCreateDialog::~TaskCreateDialog()
{
    delete ui;
}

void TaskCreateDialog::setUser(const User& user_)
{
  user = user_;
}

User& TaskCreateDialog::getUser()
{
  return user;
}
void TaskCreateDialog::setTask(const Task& task_)
{
  task = task_;
}
Task& TaskCreateDialog::getTask()
{
  return task;
}

void TaskCreateDialog::on_buttonCreateTask_clicked()
{
  Task new_task;
  task = new_task;
  emit onButtonCreateTask();
}
