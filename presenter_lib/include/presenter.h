#ifndef TASKMESSENGER_PRESENTER_H
#define TASKMESSENGER_PRESENTER_H

#include "ipresenter.h"
#include "iview.h"
#include "IClient.h"

class Presenter : public IPresenter {
public:
  Presenter() = default;
  Presenter(IView* view, IClient* client) : view(view), client(client) {}
  ~Presenter() { delete view; delete client; }

  void setView(IView* view);
  void setClient(IClient* client);

  void Authorize(std::string name) override;
  void GetTaskForUser(User user) override;
  void GetMessageForTask(Task task) override;
  void AddNewTask(Task task) override;
  void AddNewMessage(Message message) override;

private:
  IView* view;
  IClient* client;
  User user;
  Task task;
  std::vector<Task> userTasks;
  std::vector<Message> messages;
};

#endif // TASKMESSENGER_PRESENTER_H
