#include "presenter.h"

void Presenter::Authorize(std::string name) {
  User user = client->Authorize(name);
  view->showUserData(user);
}
void Presenter::GetTaskForUser(User user) {
  std::vector<Task> tasks = client->GetTaskForUser(user);
  view->showUserTasksData(tasks);
}
void Presenter::GetMessageForTask(Task task) {
  std::vector<Message> messages = client->GetMessageForTask(task);
  view->showMessagesData(messages);
}
void Presenter::AddNewTask(Task task) {
  client->AddNewTask(task);
}
void Presenter::AddNewMessage(Message message) {
  client->AddNewMessage(message);
}