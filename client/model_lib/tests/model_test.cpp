#include <gtest/gtest.h>
#include "user.h"
#include "task.h"
#include "message.h"

TEST(User, init_null) {
  User user;

  EXPECT_EQ(user.getId(), -1);
  EXPECT_EQ(user.getName(), "");
}

TEST(User, init_not_null) {
  User user(50, "Spoon");

  EXPECT_EQ(user.getId(), 50);
  EXPECT_EQ(user.getName(), "Spoon");
}

TEST(User, set_id) {
  User user;
  user.setId(332);

  EXPECT_EQ(user.getId(), 332);
}

TEST(User, set_name) {
  User user;
  user.setName("userSetName");

  EXPECT_EQ(user.getName(), "userSetName");
}

TEST(Task, init_null) {
  Task task;

  EXPECT_EQ(task.getId(), -1);
  EXPECT_EQ(task.getTitle(), "");
  EXPECT_EQ(task.getAssigner().getId(), -1);
  EXPECT_EQ(task.getWorker().getId(), -1);
}

TEST(Task, init_not_null) {
  User user1(50, "Spoon");
  User user2(100, "name");
  Task task(3, "title", user1, user2);

  EXPECT_EQ(task.getId(), 3);
  EXPECT_EQ(task.getTitle(), "title");
  EXPECT_EQ(task.getAssigner().getId(), 50);
  EXPECT_EQ(task.getWorker().getId(), 100);
}

TEST(Task, set_id) {
  Task task;
  task.setId(2);

  EXPECT_EQ(task.getId(), 2);
}

TEST(Task, set_title) {
  Task task;
  task.setTitle("my title");

  EXPECT_EQ(task.getTitle(), "my title");
}

TEST(Task, set_assigner) {
  Task task;
  User assigner(100, "name");
  task.setAssigner(assigner);

  EXPECT_EQ(task.getAssigner().getId(), 100);
}

TEST(Task, set_worker) {
  Task task;
  User worker(1444, "name");
  task.setWorker(worker);

  EXPECT_EQ(task.getWorker().getId(), 1444);
}

TEST(Message, init_null) {
  Message message;

  EXPECT_EQ(message.getId(), -1);
  EXPECT_EQ(message.getText(), "");
  EXPECT_EQ(message.getWriter().getId(), -1);
}

TEST(Message, init_not_null) {
  User user(60, "username");
  Message message(10, "my text message", user);

  EXPECT_EQ(message.getId(), 10);
  EXPECT_EQ(message.getText(), "my text message");
  EXPECT_EQ(message.getWriter().getId(), 60);
}

TEST(Message, set_Id) {
  Message message;
  message.setId(999);

  EXPECT_EQ(message.getId(), 999);
}

TEST(Message, set_Text) {
  Message message;
  message.setText("My text message");

  EXPECT_EQ(message.getText(), "My text message");
}

TEST(Message, set_Writer) {
  Message message;
  User writer(7, "ooo");
  message.setWriter(writer);

  EXPECT_EQ(message.getWriter().getId(), 7);
}
