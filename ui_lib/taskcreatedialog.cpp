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

Task& TaskCreateDialog::getTask()
{
  return task;
}

void TaskCreateDialog::on_buttonCreateTask_clicked()
{
  task.setTitle( ui->lineEdit_title->text().toStdString() );
  User worker;
  worker.setName( ui->lineEdit_executor->text().toStdString() );
  task.setWorker(worker);
  task.setAssigner(user);

  emit onButtonCreateTask();
}
