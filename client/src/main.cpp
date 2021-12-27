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

    auto view = std::make_unique<View>();
    view->mainWindow.show();
    //auto viewPtr = view.get();
    auto client = std::make_unique<ClientBoostAsio>();
    if (!client->Connect()) {
      return 11;
    }

    auto presenter = std::make_unique<Presenter>(std::move(view), std::move(client));

    //auto widget = std::make_pair(std::move(presenter), viewPtr);

    return a.exec();
}
