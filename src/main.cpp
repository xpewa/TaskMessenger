#include "../ui_lib/login.h"
#include "../ui_lib/mainwindow.h"
#include "../ui_lib/taskdialog.h"
#include "view.h"
#include "presenter.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientBoostAsio client;
    client.Connect();
    client.Run();
    View view;
    Presenter presenter(&view, &client);
    view.setPresenter(presenter);
    view.mainWindow.showMaximized();
    view.login.show();

    return a.exec();
}