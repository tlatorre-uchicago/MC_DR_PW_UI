#include "socket_com.h"
#include <iostream>


/*void socket_com::run(){

}*/

socket_com::socket_com()
{
    udpSocket = NULL;
}

void socket_com::sendDataToClient(QByteArray data){
    udpSocket->writeDatagram(data, *remoteadress, remote_port_);
}

void socket_com::connect_socket(){

    hostadress = new QHostAddress(ip_);
    remoteadress =new QHostAddress(remote_ip);

    udpSocket = new QUdpSocket(this);

    udpSocket->bind(*hostadress, local_port_);
    connect(udpSocket, &QUdpSocket::readyRead, this, &socket_com::readPendingDatagrams);
    QByteArray t;
    t.append("ok");
    sendDataToClient(t);
    emit net_ledon();
}

void socket_com::disconnect_socket(){
    delete hostadress;
    delete remoteadress;
    delete udpSocket;
    udpSocket = NULL;
}

void socket_com::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        datagram = udpSocket->receiveDatagram();
        processTheDatagram(datagram);
    }
   /* if(!connection_stablished){
        remote_port_=datagram.senderPort();
        connection_stablished=true;
    }*/
}

void socket_com::processTheDatagram(QNetworkDatagram datag){
    //char tab[1] = "\t";
std::cout<<(datag.data().toStdString())<<std::endl;
    QString word(datag.data());
    QStringList splitlist = word.split("    ");
   // std::cout<<splitlist[0].toStdString()<<std::endl;
    if(splitlist[0]=="Vd3_mon[0]:")emit vd3_1_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd2_mon[0]:")emit vd2_1_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd1_mon[0]:")emit vd1_1_chang(splitlist[1].toDouble());
    if(splitlist[0]=="G3[0]:")emit vg3_1_chang(-1*splitlist[1].toDouble());
        //std::cout<<splitlist[1].toStdString()<<std::endl;
    if(splitlist[0]=="G2[0]:")emit vg2_1_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I3[0]:")emit I3_1_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I2[0]:")emit I2_1_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vpeak[0]:")emit Vpeak_1_chang(splitlist[1].toDouble());

    if(splitlist[0]=="Vd3_mon[1]:")emit vd3_2_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd2_mon[1]:")emit vd2_2_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd1_mon[1]:")emit vd1_2_chang(splitlist[1].toDouble());
    if(splitlist[0]=="G3[1]:")emit vg3_2_chang(-1*splitlist[1].toDouble());
    if(splitlist[0]=="G2[1]:")emit vg2_2_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I3[1]:")emit I3_2_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I2[1]:")emit I2_2_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vpeak[1]:")emit Vpeak_2_chang(splitlist[1].toDouble());

    if(splitlist[0]=="Vd3_mon[2]:")emit vd3_3_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd2_mon[2]:")emit vd2_3_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd1_mon[2]:")emit vd1_3_chang(splitlist[1].toDouble());
    if(splitlist[0]=="G3[2]:")emit vg3_3_chang(-1*splitlist[1].toDouble());
    if(splitlist[0]=="G2[2]:")emit vg2_3_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I3[2]:")emit I3_3_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I2[2]:")emit I2_3_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vpeak[2]:")emit Vpeak_3_chang(splitlist[1].toDouble());

    if(splitlist[0]=="Vd3_mon[3]:")emit vd3_4_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd2_mon[3]:")emit vd2_4_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vd1_mon[3]:")emit vd1_4_chang(splitlist[1].toDouble());
    if(splitlist[0]=="G3[3]:")emit vg3_4_chang(-1*splitlist[1].toDouble());
    if(splitlist[0]=="G2[3]:")emit vg2_4_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I3[3]:")emit I3_4_chang(splitlist[1].toDouble());
    if(splitlist[0]=="I2[3]:")emit I2_4_chang(splitlist[1].toDouble());
    if(splitlist[0]=="Vpeak[3]:")emit Vpeak_4_chang(splitlist[1].toDouble());

}

void socket_com::enable_channel(int channel, int state)
{
    char command[256];

    if (!udpSocket) return;

    if (state)
        sprintf(command,"ch%i_on", channel);
    else
        sprintf(command,"ch%i_off", channel);
    sendDataToClient(QByteArray(command));
}

void socket_com::change_vc(int channel, double value)
{
    char command[256];

    if (!udpSocket) return;

    sprintf(command,"Vc_set=%i_%.2f", channel, value);
    sendDataToClient(QByteArray(command));
}

void socket_com::change_vcx(int channel, double value)
{
    char command[256];

    if (!udpSocket) return;

    sprintf(command,"Vcx_set=%i_%.2f", channel, value);
    sendDataToClient(QByteArray(command));
}

void socket_com::change_vgain(int channel, double value)
{
    char command[256];

    if (!udpSocket) return;

    sprintf(command,"Vgain_set=%i_%.2f", channel, value);
    sendDataToClient(QByteArray(command));
}
