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

void TaskCreateDialog::on_buttonCreateTask_clicked()
{

}
