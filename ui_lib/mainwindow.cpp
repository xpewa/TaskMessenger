#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

#include <QObject>

void MainWindow::addTask(Task& task)
{
  QTableWidget* table = ui->tabWidget->findChild<QWidget*>("tab")->findChild<QTableWidget*>("tableTasks");
  table->insertRow( table->rowCount() );

  QTableWidgetItem* title = new QTableWidgetItem;
  QTableWidgetItem* assigner = new QTableWidgetItem;
  QTableWidgetItem* worker = new QTableWidgetItem;

  title->setText(QString::fromStdString(task.getTitle()));
  assigner->setText(QString::fromStdString(task.getAssigner().getName()));
  worker->setText(QString::fromStdString(task.getWorker().getName()));
  size_t i = open_btn_array.size();
  open_btn_array.push_back(new QPushButton("+"));
  QObject::connect(open_btn_array[i], &QPushButton::clicked, this, &MainWindow::onButtonShowTask_clicked);

  table->setItem(table->rowCount()-1, 0, title);
  table->setItem(table->rowCount()-1, 1, assigner);
  table->setItem(table->rowCount()-1, 2, worker);
  table->setCellWidget(table->rowCount()-1, 3, open_btn_array[i]);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTableWidget* table = ui->tabWidget->findChild<QWidget*>("tab")->findChild<QTableWidget*>("tableTasks");

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
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
void MainWindow::onButtonShowTask_clicked()
{
  QObject* sender = QObject::sender();
  QPushButton* btn = qobject_cast<QPushButton*>(sender);

  int i;
  auto iter = std::find(open_btn_array.begin(), open_btn_array.end(), btn);
  if (iter != open_btn_array.end()) {
    i = std::distance(open_btn_array.begin(), iter);
  }

  user.setName(std::to_string(i));
  showUserData();

  emit onButtonShowTask(tasks[i]);
}

void MainWindow::showUserData() {
  ui->label->setText(QString::fromStdString(user.getName()));

  showTasks();
}

void MainWindow::showTasks() {
  User assigner1(0, "name1");
  User assigner2(0, "name2");
  User worker(0, "work");
  Task task(0, "title1", assigner1, worker);
  Task task2(0, "title2", assigner2, worker);
  tasks.push_back(task);
  tasks.push_back(task2);

  QTableWidget* table = ui->tabWidget->findChild<QWidget*>("tab")->findChild<QTableWidget*>("tableTasks");
  table->clear();
  table->setRowCount(0);
  open_btn_array.clear();

  for (int i = 0; i < tasks.size(); ++i) {
    addTask(tasks[i]);
  }
}


