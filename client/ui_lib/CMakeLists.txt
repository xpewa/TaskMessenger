set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(ui_lib STATIC login.cpp login.h mainwindow.cpp taskdialog.cpp taskcreatedialog.cpp)
target_link_libraries(ui_lib PUBLIC view_lib presenter_lib Qt5::Widgets)