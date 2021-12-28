#ifndef TASKMESSENGER_ICLIENT_H
#define TASKMESSENGER_ICLIENT_H

#include <string>
#include <vector>
#include "user.h"
#include "task.h"
#include "message.h"
#include "ipresenter.h"

class IClient {
public:
  virtual ~IClient() = default;
  virtual void setPresenter(IPresenter* presenter_) = 0;

  virtual User Authorize(const std::string& name) = 0;
  virtual std::vector<Task> GetTaskForUser(const User& user) = 0;
  virtual std::vector<Message> GetMessageForTask(const Task& task) = 0;
  virtual void AddNewTask(const Task& task) = 0;
  virtual void EditTask(const Task& task) = 0;
  virtual void AddNewMessage(const Task& task, const Message& message) = 0;
};

#endif // TASKMESSENGER_ICLIENT_H
