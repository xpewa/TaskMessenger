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

private slots:
    void on_buttonCreateTask_clicked();

signals:
    void onButtonCreateTask(Task task);

private:
    Ui::TaskCreateDialog *ui;
    User user;
};

#endif // TASKCREATEDIALOG_H
