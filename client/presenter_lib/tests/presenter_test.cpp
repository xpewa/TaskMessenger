#include "presenter.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IClient.h"
#include "iview.h"

using ::testing::AtLeast;
using ::testing::_;

class MockClient : public IClient {
public:
  MOCK_METHOD((User), Authorize, (std::string name));
  MOCK_METHOD((std::vector<Task> ), GetTaskForUser, (User user));
  MOCK_METHOD((std::vector<Message>), GetMessageForTask, (Task task));
  MOCK_METHOD(void, AddNewTask, (Task task));
  MOCK_METHOD(void, AddNewMessage, (Message message));
};

class MockView : public IView {
public:
  MOCK_METHOD(void, showUserData, (const User& user));
  MOCK_METHOD(void, showUserTasksData, (const std::vector<Task>& tasks));
  MOCK_METHOD(void, showTaskData, (const Task& task));
  MOCK_METHOD(void, showMessagesData, (const std::vector<Message>& messages));
};

TEST(PresenterTest, Authorize) {
  MockClient* client = new MockClient();
  auto view = std::make_unique<MockView>();
  EXPECT_CALL(*client, Authorize("name")).Times(AtLeast(1));
  EXPECT_CALL(*view, showUserData(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(client);
  presenter.setView(view);
  presenter.Authorize("name");
}

TEST(PresenterTest, GetMessageForTask) {
  MockClient* client = new MockClient();
  MockView* view = new MockView();
  EXPECT_CALL(*client, GetMessageForTask(_)).Times(AtLeast(1));
  EXPECT_CALL(*view, showMessagesData(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(client);
  presenter.setView(view);
  Task task;
  presenter.GetMessageForTask(task);
}

TEST(PresenterTest, GetTaskForUser) {
  MockClient* client = new MockClient();
  MockView* view = new MockView();
  EXPECT_CALL(*client, GetTaskForUser(_)).Times(AtLeast(1));
  EXPECT_CALL(*view, showUserTasksData(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(client);
  presenter.setView(view);
  User user;
  presenter.GetTaskForUser(user);
}

TEST(PresenterTest, AddNewTask) {
  MockClient* client = new MockClient();
  MockView* view = new MockView();
  EXPECT_CALL(*client, AddNewTask(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(client);
  presenter.setView(view);
  Task task;
  presenter.AddNewTask(task);
}

TEST(PresenterTest, AddNewMessage) {
  MockClient* client = new MockClient();
  MockView* view = new MockView();
  EXPECT_CALL(*client, AddNewMessage(_)).Times(AtLeast(1));

  Presenter presenter;
  presenter.setClient(client);
  presenter.setView(view);
  Message message;
  presenter.AddNewMessage(message);
}
