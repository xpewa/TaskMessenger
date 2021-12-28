#ifndef TASKMESSENGER_VIEW_H
#define TASKMESSENGER_VIEW_H

#include <QObject>
#include <memory>
#include "iview.h"
#include "ipresenter.h"

#include "../../ui_lib/login.h"
#include "../../ui_lib/mainwindow.h"
#include "../../ui_lib/taskdialog.h"
#include "../../ui_lib/taskcreatedialog.h"

#include <QThread>
#include <QTimer>

class View : public QObject, public IView
{

  //Q_OBJECT

public:
  View();
  ~View() = default;

  Task getTask() override;

  void setPresenter(IPresenter* presenter_) override;

  void showUserData(const User& user) override;
  void showUserTasksData(const std::vector<Task>& userTasks) override;
  void showMessagesData(const std::vector<Message>& message) override;

public slots:
  void onButtonLogin();
  void onButtonShowTask(Task &task);
  void onButtonCreateTask();
  void onButtonAddTask();
  void onButtonCreateMessage();
  void onCheckBox();
  void onActionUpdate();

private:
  IPresenter* presenter;

  void addThread(Task task);

public:
  Login login;
  MainWindow mainWindow;
  TaskDialog taskDialog;
  TaskCreateDialog taskCreateDialog;
};

#endif // TASKMESSENGER_VIEW_H
