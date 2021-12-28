#include "user.h"

User::User() { id = -1; name = ""; }
User::User(const int id_, const std::string name_) : name(name_), id(id_)
{ name = name_; id = id_; }

int User::getId() const {return id;}
std::string User::getName() const {return name;}
void User::setId(const int id_) {id = id_;}
void User::setName(const std::string name_) {name = name_;}