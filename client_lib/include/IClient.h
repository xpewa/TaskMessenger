#ifndef TASKMESSENGER_ICLIENT_H
#define TASKMESSENGER_ICLIENT_H

#include <string>
#include <vector>
#include "user.h"
#include "task.h"
#include "message.h"

class IClient {
public:
  virtual User Authorize(std::string name) = 0;
  virtual std::vector<Task> GetTaskForUser(User user) = 0;
  virtual std::vector<Message> GetMessageForTask(Task task) = 0;
  virtual void AddNewTask(Task task) = 0;
  virtual void AddNewMessage(Message message) = 0;

  //virtual ~IClient() {}
};

#endif // TASKMESSENGER_ICLIENT_H
