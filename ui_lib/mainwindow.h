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

    void showUserData(const User& user);
    void updateTasks(const std::vector<Task>& task);

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
