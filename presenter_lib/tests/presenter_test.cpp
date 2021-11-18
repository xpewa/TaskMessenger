#include "presenter.h"
#include <gmock/gmock.h>

#include "IClient.h"
#include "iview.h"

using ::testing::AtLeast;
using ::testing::_;

class MockClient : public IClient {
public:
  MOCK_METHOD((User), Authorize, (std::string));
  MOCK_METHOD((std::vector<Message>), GetMessageForTask, (Task));
  MOCK_METHOD((std::vector<Task> ), GetTaskForUser, (User));
  MOCK_METHOD(void, AddNewTask, (Task));
  MOCK_METHOD(void, AddNewMessage, (Message));
};

class MockView : public IView {
public:
  MOCK_METHOD(void, showUserData, (const User&));
  MOCK_METHOD(void, showUserTasksData, (const std::vector<Task>&));
  MOCK_METHOD(void, showTaskData, (const Task&));
  MOCK_METHOD(void, showMessagesData, (const std::vector<Message>&));
};

TEST(PresenterTest, Client_Authorize) {
  MockClient client;
  EXPECT_CALL(client, Authorize("name")).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(&client);
  presenter.Authorize("name");
}

TEST(PresenterTest, Client_GetMessageForTask) {
  MockClient client;
  EXPECT_CALL(client, GetMessageForTask(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(&client);
  Task task;
  presenter.GetMessageForTask(task);
}

TEST(PresenterTest, Client_GetTaskForUser) {
  MockClient client;
  EXPECT_CALL(client, GetTaskForUser(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(&client);
  User user;
  presenter.GetTaskForUser(user);
}

TEST(PresenterTest, Client_AddNewTask) {
  MockClient client;
  EXPECT_CALL(client, AddNewTask(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(&client);
  Task task;
  presenter.AddNewTask(task);
}

TEST(PresenterTest, Client_AddNewMessage) {
  MockClient client;
  EXPECT_CALL(client, AddNewMessage(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(&client);
  Message message;
  presenter.AddNewMessage(message);
}

TEST(PresenterTest, View_showUserData) {
  MockView view;
  EXPECT_CALL(view, showUserData(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setView(&view);
  User user;
  presenter.Authorize("name");
}

TEST(PresenterTest, View_showMessagesData) {
  MockView view;
  EXPECT_CALL(view, showMessagesData(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setView(&view);
  Task task;
  presenter.GetMessageForTask(task);
}

TEST(PresenterTest, View_showUserTasksData) {
  MockView view;
  EXPECT_CALL(view, showUserTasksData(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setView(&view);
  User user;
  presenter.GetTaskForUser(user);
}