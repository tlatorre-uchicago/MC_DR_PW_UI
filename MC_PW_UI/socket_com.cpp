#include "socket_com.h"
#include <iostream>


void socket_com::run(){

}

socket_com::socket_com(){

}

void socket_com::sendDataToClient(int data){
   const char d = data;
udpSocket->writeDatagram(&d, *hostadress, 5005);
//std::cout<<"kpahachorizozozozozo"<<std::endl;

}

int socket_com::connect_socket(){

    hostadress = new QHostAddress(ip_);

    udpSocket = new QUdpSocket(this);
    //udpSocket->bind(QHostAddress::LocalHost, 7755);

    //connect(udpSocket, &QUdpSocket::readyRead,this, &Server::readPendingDatagrams);
    udpSocket->bind(*hostadress, 5005);
    connect(udpSocket, &QUdpSocket::readyRead, this, &socket_com::readPendingDatagrams);
}

int socket_com::disconnect_socket(){

    delete hostadress;
    delete udpSocket;
}

void socket_com::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        datagram = udpSocket->receiveDatagram();
        //processTheDatagram(datagram);
    }
}
