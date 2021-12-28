#ifndef TASKMESSENGER_PRESENTER_H
#define TASKMESSENGER_PRESENTER_H

#include <memory>

#include "ipresenter.h"
#include "iview.h"
#include "IClient.h"

class Presenter : public IPresenter {
public:
  Presenter(std::unique_ptr<IView> view_, std::unique_ptr<IClient> client_)
      : view(std::move(view_)), client(std::move(client_)) {
      view->setPresenter(this);
      client->setPresenter(this); }
  ~Presenter() override = default;

  void Authorize(std::string name) override;
  void GetTaskForUser(User user) override;
  void GetMessageForTask(Task task) override;
  void AddNewTask(Task task) override;
  void EditTask(Task task) override;
  void AddNewMessage(Task task, Message message) override;

  void UpdateMessageForTask(Task task, std::vector<Message> messages) override;

private:
  std::unique_ptr<IView> view;
  std::unique_ptr<IClient> client;
  User user;
  std::vector<Task> userTasks;
  std::vector<Message> messages;
};

#endif // TASKMESSENGER_PRESENTER_H
