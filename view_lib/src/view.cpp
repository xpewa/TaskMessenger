#include "view.h"


View::View() {
  presenter = nullptr;

  QObject::connect(&mainWindow, &MainWindow::onButtonAddTask, this, &View::onButtonCreateTask);
  QObject::connect(&mainWindow, &MainWindow::onButtonShowTask, this, &View::onButtonShowTask);
  QObject::connect(&login, &Login::onButtonLogin, this, &View::onButtonLogin);
  QObject::connect(&taskDialog, &TaskDialog::onButtonSendMessage, this, &View::onButtonCreateMessage);
}

View::~View() { delete presenter; }

void View::setPresenter(IPresenter& presenter) {}

void View::showUserData(const User& user) {
  mainWindow.setUser(user);
  mainWindow.showUserData();
}
void View::showUserTasksData(const std::vector<Task>& userTasks) {
  mainWindow.setTasks(userTasks);
  mainWindow.showTasks();
}
void View::showTaskData(const Task& task) {}
void View::showMessagesData(const std::vector<Message>& message) {}

void View::onButtonLogin() {}
void View::onButtonShowTask(Task &task) {
  taskDialog.setUser(mainWindow.getUser());
  taskDialog.setTask(task);
  taskDialog.updateTaskData(task);
  //presenter->GetMessageForTask(task);

  taskDialog.setModal(true);
  taskDialog.exec();
}
void View::onButtonCreateTask() {
  User user_(1, "my_name");
  showUserData(user_);

  taskCreateDialog.setModal(true);
  taskCreateDialog.exec();
}
void View::onButtonCreateMessage() {}