#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

User& Login::getUser()
{
  return user;
}

void Login::on_buttonLogin_clicked()
{
  user.setName(ui->lineEdit->text().toStdString());
  emit onButtonLogin();
}
