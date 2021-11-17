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

void TaskCreateDialog::on_buttonCreateTask_clicked()
{
  Task task;
  emit onButtonCreateTask(task);
}
