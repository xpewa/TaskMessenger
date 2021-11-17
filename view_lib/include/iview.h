#ifndef TASKMESSENGER_IVIEW_H
#define TASKMESSENGER_IVIEW_H

#include "user.h"
#include <vector>

class IView {
public:
  virtual void showUserData(const User& user) = 0;
  virtual void showUserTasksData(const std::vector<Task>& userTasks) = 0;
  virtual void showTaskData(const Task& task) = 0;
  virtual void showMessagesData(const std::vector<Message>& message) = 0;
};

#endif // TASKMESSENGER_IVIEW_H
