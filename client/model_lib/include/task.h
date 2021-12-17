#ifndef TASKMESSENGER_TASK_H
#define TASKMESSENGER_TASK_H

#include "user.h"

class Task {
public:
  Task();
  Task(const int id_, const  std::string title_,
       const User assigner_, const User worker_);
  ~Task() = default;

  void setId(const int id_);
  void setTitle(const std::string title_);
  void setAssigner(const User assigner_);
  void setWorker(const User worker_);
  int getId() const;
  std::string getTitle() const;
  User getAssigner() const;
  User getWorker() const;
private:
  int id;
  std::string title;
  User assigner;
  User worker;
};

#endif // TASKMESSENGER_TASK_H
