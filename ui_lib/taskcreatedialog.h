#ifndef TASKCREATEDIALOG_H
#define TASKCREATEDIALOG_H

#include <QDialog>
#include "user.h"

namespace Ui {
class TaskCreateDialog;
}

class TaskCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskCreateDialog(QWidget *parent = nullptr);
    ~TaskCreateDialog();

    void setUser(const User& user_);
    User& getUser();
    void setTask(const Task& task_);
    Task& getTask();

private slots:
    void on_buttonCreateTask_clicked();

signals:
    void onButtonCreateTask();

private:
    Ui::TaskCreateDialog *ui;
    User user;
    Task task;
};

#endif // TASKCREATEDIALOG_H
