#include "message.h"

Message::Message() : id(-1), text(""), writer(User()) {}
Message::Message(const int id_, const std::string text_, const User writer_)
    : writer(writer_), text(text_), id(id_) {}

void Message::setId(const int id_) { id = id_; }
void Message::setText(const std::string text_) { text = text_; }
void Message::setWriter(const User writer_) { writer = writer_; }
int Message::getId() { return id; }
std::string Message::getText() { return text; }
User Message::getWriter() { return writer; }