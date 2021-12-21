#include "presenter.h"

void Presenter::Authorize(std::string name) {
  user = client->Authorize(name);
  view->showUserData(user);
}
void Presenter::GetTaskForUser(User user) {
  userTasks = client->GetTaskForUser(user);
  view->showUserTasksData(userTasks);
}
void Presenter::GetMessageForTask(Task task) {
  messages = client->GetMessageForTask(task);
  view->showMessagesData(messages);
}
void Presenter::AddNewTask(Task task) {
  client->AddNewTask(task);
}
void Presenter::AddNewMessage(Task task, Message message) {
  client->AddNewMessage(task, message);
}