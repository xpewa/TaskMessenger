#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <user.h>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void setUser(const User& user_);
    User& getUser();

private slots:
    void on_buttonLogin_clicked();

signals:
    void onButtonLogin();

private:
    Ui::Login *ui;
    User user;
};

#endif // LOGIN_H
