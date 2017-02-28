#include "sender.h"

Sender::Sender()
{

    QHostAddress address;
    foreach(QHostAddress a, QNetworkInterface::allAddresses())
    {
        // use the first non-localhost IPv4 address
        if( a != QHostAddress::LocalHost && a.toIPv4Address() )
        {
            address = a;
            qDebug() << address.toString();
            break;

        }
    }

    Q_ASSERT( !address.isNull() );
    //this->listen( address, port );
}

Sender::Sender(quint32 port)
{

    hasConnections = 0;
    if(!this->listen(QHostAddress::Any,port))
    {

        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(this->errorString());
    }
    else
    {

        qDebug() << QString::fromUtf8("server started");
        this->waitForNewConnection();
    }
}

void Sender::startServer(quint16 port)
{
    hasConnections = 0;
    if(!this->listen(QHostAddress::Any,port))
    {

        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(this->errorString());
    }
    else
    {

        qDebug() << QString::fromUtf8("server started");
        this->waitForNewConnection();
    }
}

void Sender::sendData(QTcpSocket *socket, QByteArray data)
{

    QByteArray mess;
    QDataStream out(&mess, QIODevice::Append);
    out.setByteOrder(QDataStream::LittleEndian);

    out<<quint32(this->uniqword)<<data;
    //out<<quint32(data.length());
    //out<<data;
    //socket
    int a=*((int*)mess.constData());
    int b=*((int*)mess.constData()+4);
    socket->write(mess);

}
