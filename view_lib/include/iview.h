#ifndef TASKMESSENGER_IVIEW_H
#define TASKMESSENGER_IVIEW_H

#include "user.h"
#include <vector>

class IView {
public:
  virtual void showUserData(User user) = 0;
  virtual void showUserTasksData(std::vector<Task> userTasks) = 0;
  virtual void showTaskData(Task task) = 0;
  virtual void showMessageData(Message message) = 0;
};

#endif // TASKMESSENGER_IVIEW_H
