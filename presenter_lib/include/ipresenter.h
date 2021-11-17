#ifndef TASKMESSENGER_IPRESENTER_H
#define TASKMESSENGER_IPRESENTER_H

#include <string>
#include "user.h"

class IPresenter {
public:
  virtual void Authorize(std::string name) = 0;
  virtual void GetTaskForUser(User user) = 0;
  virtual void GetMessageForTask(Task task) = 0;
  virtual void AddNewTask(Task task) = 0;
  virtual void AddNewMessage(Message message) = 0;
};

#endif // TASKMESSENGER_IPRESENTER_H
