#ifndef TASKMESSENGER_USER_H
#define TASKMESSENGER_USER_H

#include <string>

class User {
public:
  User();
  User(const int id_, const std::string name_) ;
  ~User() = default;

  int getId();
  std::string getName();
  void setId(const int id_);
  void setName(const std::string name_);

private:
  int id;
  std::string name;
};

#endif // TASKMESSENGER_USER_H
