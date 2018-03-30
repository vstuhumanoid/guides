#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка слотов и сигналов
    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(btn1_pressed()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(btn2_pressed()));

    cnt1 = 0;
    cnt2 = 0;

    ui->txt1->setText(QString::number(cnt1));
    ui->txt2->setText(QString::number(cnt2));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn1_pressed()
{
    cnt1++;
    ui->txt1->setText(QString::number(cnt1));
}

void MainWindow::btn2_pressed()
{
    cnt2++;
    ui->txt2->setText(QString::number(cnt2));
}
