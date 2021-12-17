#ifndef TASKMESSENGER_MESSAGE_H
#define TASKMESSENGER_MESSAGE_H

#include "user.h"

class Message {
public:
  Message();
  Message(const int id_, const std::string text_, const User writer_);
  ~Message() = default;

  void setId(const int id_);
  void setText(const std::string text_);
  void setWriter(const User writer_);
  int getId() const;
  std::string getText() const;
  User getWriter() const;
private:
  int id;
  std::string text;
  User writer;
};

#endif // TASKMESSENGER_MESSAGE_H
