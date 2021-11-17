#ifndef TASKMESSENGER_VIEW_H
#define TASKMESSENGER_VIEW_H

#include <QObject>
#include "iview.h"
#include "ipresenter.h"

#include "../../ui_lib/login.h"
#include "../../ui_lib/mainwindow.h"
#include "../../ui_lib/taskdialog.h"
#include "../../ui_lib/taskcreatedialog.h"

class View : public QObject, public IView
{

  //Q_OBJECT

public:
  View();
  View(IPresenter* presenter) : presenter(presenter) {}
  ~View();

  void setPresenter(IPresenter& presenter);

  void showUserData(User user) override;
  void showUserTasksData(std::vector<Task> userTasks) override;
  void showTaskData(Task task) override;
  void showMessageData(Message message) override;

public slots:
  void onButtonLogin(std::string name);
  void onButtonShowTask();
  void onButtonCreateTask(Task task);
  void onButtonCreateMessage(Message message);

private:
  IPresenter* presenter;
public:
  Login login;
  MainWindow mainWindow;
  TaskDialog taskDialog;
  TaskCreateDialog taskCreateDialog;
};

#endif // TASKMESSENGER_VIEW_H
