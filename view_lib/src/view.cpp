#include "view.h"

//пробую использовать сигналы и слоты

View::View() {
  presenter = nullptr;

  QObject::connect(&mainWindow, &MainWindow::onButtonAddTask, this, &View::onButtonShowTask);
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
void View::onButtonShowTask() {
  User user_(1, "my_name");
  showUserData(user_);

  taskCreateDialog.setModal(true);
  taskCreateDialog.exec();
}
void View::onButtonCreateTask() {}
void View::onButtonCreateMessage() {}