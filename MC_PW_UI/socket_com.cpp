#include "socket_com.h"
#include <iostream>


/*void socket_com::run(){

}*/

socket_com::socket_com(){
    //connect_socket();
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

void socket_com::ch1(int state){
    if(state)Data_onoff.append("ch1_on");
    else Data_onoff.append("ch1_off");
    sendDataToClient(Data_onoff);
   // std::cout<<Data_onoff.toStdString()<<std::endl;
    Data_onoff.clear();
}
void socket_com::ch2(int state){
    if(state)Data_onoff.append("ch2_on");
    else Data_onoff.append("ch2_off");
    sendDataToClient(Data_onoff);
   // std::cout<<Data_onoff.toStdString()<<std::endl;
    Data_onoff.clear();
}
void socket_com::ch3(int state){
    if(state)Data_onoff.append("ch3_on");
    else Data_onoff.append("ch3_off");
    sendDataToClient(Data_onoff);
   // std::cout<<Data_onoff.toStdString()<<std::endl;
    Data_onoff.clear();
}
void socket_com::ch4(int state){
    if(state)Data_onoff.append("ch4_on");
    else Data_onoff.append("ch4_off");
    sendDataToClient(Data_onoff);
   // std::cout<<Data_onoff.toStdString()<<std::endl;
    Data_onoff.clear();
}

void socket_com::vc1(double val){
    Data_todev.append("Vc_set=1_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}
void socket_com::vc2(double val){
    Data_todev.append("Vc_set=2_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_onoff.toStdString()<<std::endl;
    Data_todev.clear();
}
void socket_com::vc3(double val){
    Data_todev.append("Vc_set=3_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_onoff.toStdString()<<std::endl;
    Data_todev.clear();
}
void socket_com::vc4(double val){
    Data_todev.append("Vc_set=4_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_onoff.toStdString()<<std::endl;
    Data_todev.clear();
}


void socket_com::vcx1(double val){
    Data_todev.append("Vcx_set=1_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}

void socket_com::vcx2(double val){
    Data_todev.append("Vcx_set=2_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}

void socket_com::vcx3(double val){
    Data_todev.append("Vcx_set=3_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}

void socket_com::vcx4(double val){
    Data_todev.append("Vcx_set=4_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}


void socket_com::vgain1(double val){
    Data_todev.append("Vgain_set=1_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}
void socket_com::vgain2(double val){
    Data_todev.append("Vgain_set=2_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}
void socket_com::vgain3(double val){
    Data_todev.append("Vgain_set=3_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}
void socket_com::vgain4(double val){
    Data_todev.append("Vgain_set=4_");
    Data_todev.append(QString::number(val).toUtf8());
    sendDataToClient(Data_todev);
   //std::cout<<Data_todev.toStdString()<<std::endl;
    Data_todev.clear();
}
