#ifndef QT_TEST_MAINWINDOW_H
#define QT_TEST_MAINWINDOW_H

#include <QtWidgets>

namespace  Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow* ui;
    int cnt1, cnt2;

private slots:
    void btn1_pressed();
    void btn2_pressed();
};


#endif //QT_TEST_MAINWINDOW_H
