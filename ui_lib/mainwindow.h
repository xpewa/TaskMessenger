#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"

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
    void updateTasks();

public slots:
    void on_buttonAddTask_clicked();

signals:
    void onButtonAddTask();

private:
    Ui::MainWindow *ui;
    User user;
    std::vector<Task> tasks;
};
#endif // MAINWINDOW_H
