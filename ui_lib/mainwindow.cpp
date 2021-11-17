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

void MainWindow::setUser(const User& user_)
{
  user = user_;
}

void MainWindow::setTasks(const std::vector<Task>& tasks_)
{
  tasks = tasks_;
}
User& MainWindow::getUser()
{
  return user;
}
std::vector<Task>& MainWindow::getTasks()
{
  return tasks;
}

void MainWindow::on_buttonAddTask_clicked()
{
    emit onButtonAddTask();
}

void MainWindow::showUserData() {
  ui->label->setText(QString::fromStdString(user.getName()));
}

void MainWindow::updateTasks() {}


