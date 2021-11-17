#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskcreatedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAddTask_clicked()
{
    emit onButtonAddTask();
}

void MainWindow::showUserData(const User& new_user) {
  user = new_user;
  ui->label->setText(QString::fromStdString(user.getName()));
}


