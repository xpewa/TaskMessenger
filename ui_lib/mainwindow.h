#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "task.h"
#include "message.h"

#include "taskcreatedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUser(const User& user_);
    void setTasks(const std::vector<Task>& tasks_);
    User& getUser();
    std::vector<Task>& getTasks();

    void showUserData();
    void showTasks();

public slots:
    void on_buttonAddTask_clicked();
    void onButtonShowTask_clicked();

signals:
    void onButtonAddTask();
    void onButtonShowTask(Task &task);

private:
    void addTask(Task& task);

    Ui::MainWindow *ui;
    User user;
    std::vector<Task> tasks;
    std::vector<QPushButton*> open_btn_array;
};
#endif // MAINWINDOW_H
