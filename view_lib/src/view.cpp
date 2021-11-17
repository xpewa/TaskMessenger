#include "view.h"

//пробую использовать сигналы и слоты

View::View() {

  QObject::connect(&mainWindow, &MainWindow::onButtonAddTask, this, &View::onButtonShowTask);

  //QObject::connect(this, &View::showUser, &mainWindow, &MainWindow::showUserData);
  //QObject::connect(this, SIGNAL(showUser(User)), &mainWindow, SLOT(showUserData(User)));
}

View::~View() { delete presenter; }

void View::setPresenter(IPresenter& presenter) {}

void View::showUserData(User user) {
  mainWindow.showUserData(user);
}
void View::showUserTasksData(std::vector<Task> userTasks) {}
void View::showTaskData(Task task) {}
void View::showMessageData(Message message) {}

void View::onButtonShowTask() {
  User user_(1, "my_name");
  //emit showUser(user);
  showUserData(user_);

  taskCreateDialog.setModal(true);
  taskCreateDialog.exec();
}