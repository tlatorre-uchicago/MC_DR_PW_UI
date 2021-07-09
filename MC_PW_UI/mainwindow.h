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
    int loadFromFile(char *filename);
    int saveToFile(char *filename);

public slots:
    void turnoff();
    void ledon();
    void updateUI();

private:
    Ui::MainWindow *ui;
    socket_com *com;
    int last_channel_state[4];
    double last_vc[4];
    double last_vcx[4];
    double last_vgain[4];

signals:
    void disconnect_socket();

};
#endif // MAINWINDOW_H
