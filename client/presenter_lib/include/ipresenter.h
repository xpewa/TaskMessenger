#ifndef TASKMESSENGER_IPRESENTER_H
#define TASKMESSENGER_IPRESENTER_H

#include <string>
#include "user.h"
#include "task.h"
#include "message.h"

#include <vector>

class IPresenter {
public:
  virtual ~IPresenter() = default;

  virtual void Authorize(std::string name) = 0;
  virtual void GetTaskForUser(User user) = 0;
  virtual void GetMessageForTask(Task task) = 0;
  virtual void AddNewTask(Task task) = 0;
  virtual void EditTask(Task task) = 0;
  virtual void AddNewMessage(Task task, Message message) = 0;

  virtual void UpdateMessageForTask(Task task, std::vector<Message> messages) = 0;
};

#endif // TASKMESSENGER_IPRESENTER_H
