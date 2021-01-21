#ifndef SOCKET_COM_H
#define SOCKET_COM_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
//#include <QThread>
#include <QNetworkDatagram>
#include <iostream>

#define localsocket 55180
#define remotesocket 5005


class socket_com : public QObject
{
    Q_OBJECT
public:
    //void run();
    explicit socket_com();


    void readPendingDatagrams(); 
    void processTheDatagram(QNetworkDatagram datag);
    bool connection_stablished = false;
    //int remotesocket;
    QByteArray Data_onoff;
    QByteArray Data_todev;

    QUdpSocket *udpSocket;
    QHostAddress *hostadress;
    QHostAddress *remoteadress;
    QNetworkDatagram datagram;

signals:
    void vd1_1_chang(double val);
    void vd2_1_chang(double val);
    void vd3_1_chang(double val);
    void vg2_1_chang(double val);
    void vg3_1_chang(double val);
    void I3_1_chang(double val);
    void I2_1_chang(double val);
    void Vpeak_1_chang(double val);

    void vd1_2_chang(double val);
    void vd2_2_chang(double val);
    void vd3_2_chang(double val);
    void vg2_2_chang(double val);
    void vg3_2_chang(double val);
    void I3_2_chang(double val);
    void I2_2_chang(double val);
    void Vpeak_2_chang(double val);

    void vd1_3_chang(double val);
    void vd2_3_chang(double val);
    void vd3_3_chang(double val);
    void vg2_3_chang(double val);
    void vg3_3_chang(double val);
    void I3_3_chang(double val);
    void I2_3_chang(double val);
    void Vpeak_3_chang(double val);

    void vd1_4_chang(double val);
    void vd2_4_chang(double val);
    void vd3_4_chang(double val);
    void vg2_4_chang(double val);
    void vg3_4_chang(double val);
    void I3_4_chang(double val);
    void I2_4_chang(double val);
    void Vpeak_4_chang(double val);

    void net_ledon();

public slots:
    void connect_socket();
    void disconnect_socket();
    void sendDataToClient(QByteArray data);
    void ch1(int state);
    void ch2(int state);
    void ch3(int state);
    void ch4(int state);

    void vc1(double val);
    void vc2(double val);
    void vc3(double val);
    void vc4(double val);
    void vcx1(double val);
    void vcx2(double val);
    void vcx3(double val);
    void vcx4(double val);
    void vgain1(double val);
    void vgain2(double val);
    void vgain3(double val);
    void vgain4(double val);

    void set_network_ip(QString ip){remote_ip=ip;}
    void set_network_local_port_(QString port){local_port_=port.toInt();}
    void set_network_remote_port_(QString port){remote_port_=port.toInt();}

private:
    //bool connected;
    QString ip_;
    QString remote_ip;// = "192.168.0.101";
    int local_port_;//= localsocket;
    int remote_port_;//= remotesocket;
};

#endif // SOCKET_COM_H
