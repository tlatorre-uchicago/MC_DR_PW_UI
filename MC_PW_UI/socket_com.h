#ifndef SOCKET_COM_H
#define SOCKET_COM_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QThread>

class socket_com : public QThread
{
    Q_OBJECT
public:
    void run();
    explicit socket_com();
    int connect_socket();
    int disconnect_socket();
    void readPendingDatagrams();
    QUdpSocket *udpSocket;
    QHostAddress *hostadress;
    QNetworkDatagram datagram;

signals:
    void vg3_1_chang(double val);

public slots:
    void sendDataToClient(int data);

private:
    bool connected;
    QString ip_;
    QString local_port_;
    QString remote_port_;
};

#endif // SOCKET_COM_H
