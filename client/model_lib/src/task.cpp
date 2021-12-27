#include "task.h"

Task::Task() : id(-1), title(""), assigner(User()), worker(User()), done(false) {}
Task::Task(const int id_, const  std::string title_,
           const User assigner_, const User worker_, bool done_)
    : id(id_), title(title_), assigner(assigner_), worker(User(worker_)), done(done_) {}

void Task::setId(const int id_) { id = id_; }
void Task::setTitle(const std::string title_) { title = title_; }
void Task::setAssigner(const User assigner_) { assigner = assigner_; }
void Task::setWorker(const User worker_) { worker = worker_; }
void Task::setDone(bool done_) { done = done_; }
int Task::getId() const { return id;}
std::string Task::getTitle() const { return title; }
User Task::getAssigner() const { return assigner; }
User Task::getWorker() const { return worker; }
bool Task::getDone() const { return done; }