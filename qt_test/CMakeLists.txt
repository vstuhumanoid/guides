cmake_minimum_required(VERSION 3.9)
project(qt_test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)

find_package (Qt5Core)
find_package (Qt5Widgets)

# Определяем цель сборки
qt5_wrap_ui(QT_TEST_UI_HEADERS  mainwindow/mainwindow.ui)                           # UI-файлы
add_executable(qt_test main.cpp mainwindow/mainwindow.cpp ${QT_TEST_UI_HEADERS})    # Исполняемые файлы
target_link_libraries(qt_test ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES})         # Линковка библиотек