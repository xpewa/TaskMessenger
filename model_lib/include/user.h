#ifndef TASKMESSENGER_USER_H
#define TASKMESSENGER_USER_H

#include <string>

class User {
public:
  User() : id(0), name("") {}
  User(const int id_, const std::string name_) : name(name_), id(id_) {}
  ~User() = default;

  int getId() {return id;}
  std::string getName() {return name;}
  void setId(const int id_) {id = id_;}
  void setName(const std::string name_) {name = name_;}

private:
  int id;
  std::string name;
};

//для тестов

class Task {
public:
  void setTitle(std::string title_) { title = title_; }
  std::string getTitle() { return title; }
private:
  std::string title;
};
class Message {
public:
  void setText(std::string text_) { text = text_; }
  std::string getText() { return text; }
private:
  std::string text;
};

#endif // TASKMESSENGER_USER_H
