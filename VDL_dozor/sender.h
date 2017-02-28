#ifndef SENDER_H
#define SENDER_H

#include <QDataStream>
#include <QTcpSocket>
#include <QTcpServer>
#include <QNetworkInterface>
#include <boost/circular_buffer.hpp>
#include <boost/circular_buffer/base.hpp>
#include <boost/circular_buffer/debug.hpp>
#include <boost/circular_buffer/details.hpp>
#include <boost/circular_buffer/space_optimized.hpp>
class Sender : public QTcpServer
{
public:
    Sender();
    Sender(quint32 port);
    // QTcpSocket *clientSocket;
    static const quint32 uniqword = 0xAABB01DD;
    int hasConnections;
    boost::circular_buffer <QByteArray> CB;
    QMap<int,QTcpSocket *> clientList;


    void startServer(quint16 port);
public slots:
    void sendData(QTcpSocket *socket, QByteArray data);

};

#endif // SENDER_H
