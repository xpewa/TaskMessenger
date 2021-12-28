#include "taskdialog.h"
#include "ui_taskdialog.h"

TaskDialog::TaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskDialog)
{
    ui->setupUi(this);
}

TaskDialog::~TaskDialog()
{
    delete ui;
}

void TaskDialog::setUser(const User& user_)
{
  user = user_;
}
void TaskDialog::setTask(const Task& task_)
{
  task = task_;
}
void TaskDialog::pushBackMessage(const Message& message_)
{
  messages.push_back(message_);
}
void TaskDialog::setMessages(const std::vector<Message>& messages_)
{
  messages = messages_;
}
User& TaskDialog::getUser()
{
  return user;
}
Task& TaskDialog::getTask()
{
  return task;
}
Message& TaskDialog::getMessage()
{
  return message;
}
std::vector<Message>& TaskDialog::getMessages()
{
  return messages;
}

void TaskDialog::updateTaskData(Task& task) {
  ui->label->setText(QString::fromStdString(task.getTitle()));
  ui->checkBox->setChecked(task.getDone());

  //
  //messages.clear();
  //updateMessages();
  //
}

void TaskDialog::addMessage(Message message) {
  std::string str = message.getWriter().getName() + " : " + message.getText();
  ui->listWidget->addItem(QString::fromStdString(str));
}

void TaskDialog::updateMessages() {
  //
  //User user(10, "Аполлинарий");
  //Message message(0, "Привет! Это текст сообщения.", user);
  //messages.push_back(message);
  //

  ui->listWidget->clear();

  for (int i = 0; i < messages.size(); ++i) {
    addMessage(messages[i]);
  }
}

void TaskDialog::on_buttonSendMessage_clicked()
{
  message.setWriter(user);
  message.setText( ui->plainTextEdit->toPlainText().toStdString() );
  ui->plainTextEdit->clear();
  emit onButtonSendMessage();
}

void TaskDialog::on_checkBox_stateChanged(int arg1)
{
  task.setDone(arg1);
  emit onCheckBox();
}
