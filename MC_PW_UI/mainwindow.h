#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "socket_com.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void turnoff();
    void ledon();

private:
    Ui::MainWindow *ui;
    socket_com *com;

signals:
    void disconnect_socket();

};
#endif // MAINWINDOW_H
