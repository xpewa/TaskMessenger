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

void Login::on_buttonLogin_clicked()
{
  std::string name = ui->lineEdit->text().toStdString();
  emit onButtonLogin(name);
}
