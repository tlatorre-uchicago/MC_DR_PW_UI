#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("INQNET - Macom power distribution"));
    com = new socket_com();
    QObject::connect(com, SIGNAL(vg3_1_chang(double)), ui->vg3_1, SLOT(display(double)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

