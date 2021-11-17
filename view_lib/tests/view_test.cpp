#include "user.h"
#include "view.h"
#include <QApplication>
#include <gtest/gtest.h>

TEST(View, show_user_data) {
  View view;
  User user(1, "ttt");
  view.showUserData(user);

  EXPECT_EQ(view.mainWindow.getUser().getName(), "ttt");
}

TEST(View, show_user_tasks_data) {
  View view;
  std::vector<Task> tasks;
  Task task;
  tasks.push_back(task);
  view.showUserTasksData(tasks);

  EXPECT_EQ(view.mainWindow.getTasks().size(), 1);
}

TEST(View, show_task_data) {
  View view;
  Task task;
  task.setTitle("title");
  view.showTaskData(task);

  EXPECT_EQ(view.taskDialog.getTask().getTitle(), "title");
}

TEST(View, show_message_data) {
  View view;
  std::vector<Message> messages;
  Message message1;
  Message message2;
  messages.push_back(message1);
  messages.push_back(message2);

  view.showMessagesData(messages);

  EXPECT_EQ(view.taskDialog.getMessages().size(), 2);
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  return RUN_ALL_TESTS();
}
