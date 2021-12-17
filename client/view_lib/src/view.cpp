#include "view.h"


View::View() {
  presenter = nullptr;

  QObject::connect(&mainWindow, &MainWindow::onButtonCreateTask, this, &View::onButtonCreateTask);
  QObject::connect(&taskCreateDialog, &TaskCreateDialog::onButtonCreateTask, this, &View::onButtonAddTask);
  QObject::connect(&mainWindow, &MainWindow::onButtonShowTask, this, &View::onButtonShowTask);
  QObject::connect(&login, &Login::onButtonLogin, this, &View::onButtonLogin);
  QObject::connect(&taskDialog, &TaskDialog::onButtonSendMessage, this, &View::onButtonCreateMessage);
}

void View::setPresenter(IPresenter* presenter_) { presenter = presenter_; }

void View::showUserData(const User& user) {
  mainWindow.setUser(user);
  mainWindow.showUserData();

  presenter->GetTaskForUser(user);
}

void View::showUserTasksData(const std::vector<Task>& userTasks) {
  mainWindow.setTasks(userTasks);
  mainWindow.showTasks();
}

void View::showMessagesData(const std::vector<Message>& message) {
  taskDialog.setMessages(message);
  taskDialog.updateMessages();
}

void View::onButtonLogin() {
  User user = login.getUser();
  presenter->Authorize(user.getName());
  login.close();
  mainWindow.showMaximized();
}

void View::onButtonShowTask(Task &task) {
  taskDialog.setUser(mainWindow.getUser());
  taskDialog.setTask(task);
  taskDialog.updateTaskData(task);
  presenter->GetMessageForTask(task);

  taskDialog.setModal(true);
  taskDialog.exec();
}
void View::onButtonCreateTask() {
  //
  //User user_(1, "Боб");
  //showUserData(user_);
  //

  taskCreateDialog.setUser( mainWindow.getUser() );
  taskCreateDialog.setModal(true);
  taskCreateDialog.exec();
}
void View::onButtonAddTask() {
  Task task = taskCreateDialog.getTask();

  taskCreateDialog.close();
  mainWindow.pushBackTask(task);
  mainWindow.showTasks();
  presenter->AddNewTask(task);
}
void View::onButtonCreateMessage() {
  Message message = taskDialog.getMessage();

  taskDialog.pushBackMessage(message);
  taskDialog.updateMessages();
  presenter->AddNewMessage(message);
}