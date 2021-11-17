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

    void showUserData(User user);

public slots:
    void on_buttonAddTask_clicked();
    //void showUserData(User user);

signals:
    void onButtonAddTask();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
