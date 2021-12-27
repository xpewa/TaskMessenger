#include "view.h"


View::View() {
  presenter = nullptr;

  QObject::connect(&mainWindow, &MainWindow::onButtonCreateTask, this, &View::onButtonCreateTask);
  QObject::connect(&taskCreateDialog, &TaskCreateDialog::onButtonCreateTask, this, &View::onButtonAddTask);
  QObject::connect(&mainWindow, &MainWindow::onButtonShowTask, this, &View::onButtonShowTask);
  QObject::connect(&mainWindow, &MainWindow::onActionUpdate, this, &View::onActionUpdate);
  QObject::connect(&login, &Login::onButtonLogin, this, &View::onButtonLogin);
  QObject::connect(&taskDialog, &TaskDialog::onButtonSendMessage, this, &View::onButtonCreateMessage);
  QObject::connect(&taskDialog, &TaskDialog::onCheckBox, this, &View::onCheckBox);

  //QObject::connect(&thread2, &QThread::started, this, &View::run);
  //QObject::connect(this, &View::close, &thread2, &QThread::terminate);
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
  std::vector<Message> messages;
  taskDialog.setMessages(messages);
  taskDialog.updateMessages();
  presenter->GetMessageForTask(task);

  taskDialog.setModal(true);
  taskDialog.exec();

  thread2.start();
  while (taskDialog.isVisible()) {
    run(task);
  }
  thread2.terminate();
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
  //mainWindow.pushBackTask(task);
  //mainWindow.showTasks();
  presenter->AddNewTask(task);

  User user = mainWindow.getUser();
  presenter->GetTaskForUser(user);
}
void View::onButtonCreateMessage() {
  Message message = taskDialog.getMessage();
  Task task = taskDialog.getTask();

  taskDialog.pushBackMessage(message);
  taskDialog.updateMessages();
  presenter->AddNewMessage(task, message);
}

void View::onCheckBox() {
  Task task = taskDialog.getTask();

  std::vector<Task> tasks = mainWindow.getTasks();
  for (int i = 0; i < tasks.size(); ++i) {
    if (task.getId() == tasks[i].getId()) {
      tasks[i] = task;
    }
  }
  mainWindow.setTasks(tasks);

  presenter->EditTask(task);
}

void View::onActionUpdate() {
  User user = mainWindow.getUser();
  presenter->GetTaskForUser(user);
}

Task View::getTask() {
  return taskDialog.getTask();
}

void View::run(Task &task) {
  thread2.sleep(1);

  presenter->GetMessageForTask(task);
}