#ifndef TASKMESSENGER_IVIEW_H
#define TASKMESSENGER_IVIEW_H

#include "user.h"
#include "task.h"
#include "message.h"
#include "ipresenter.h"
#include <vector>

class IView {
public:
  virtual void showUserData(const User& user) = 0;
  virtual void showUserTasksData(const std::vector<Task>& userTasks) = 0;
  virtual void showMessagesData(const std::vector<Message>& message) = 0;

  virtual void setPresenter(IPresenter* presenter_) = 0;
  virtual Task getTask() = 0;
  virtual ~IView() = default;
};

#endif // TASKMESSENGER_IVIEW_H
