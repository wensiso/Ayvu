/*
 * server.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include "server.h"

namespace ayvu {

Server::Server(QObject *parent)
     : QTcpServer(parent)
 {
    m_connection = 0;
    connect(this, SIGNAL(newConnection(Connection*)), this, SLOT(onNewConnection(Connection*)));
 }

void Server::start()
{
    QHostAddress host = Network::getValidIP();

    bool ret = this->listen(host, REQUEST_PORT);
    if (ret) {
        qDebug() << "[SessionServer]: The server is running on " + host.toString() + ":"
                                    + QString::number(REQUEST_PORT);
    } else {
        qWarning() << "[SessionServer]: Unable to start the server on " + host.toString() + ":"
                                  + QString::number(REQUEST_PORT);
        return;
    }
    Q_ASSERT(ret);
}

 void Server::incomingConnection(int socketDescriptor)
 {
     m_connection = new Connection(this);
     m_connection->setSocketDescriptor(socketDescriptor);
     qDebug() << "[SessionServer]: Emiting event: newConnection";
     emit newConnection(m_connection);
 }

 void Server::onNewConnection(Connection* newConnection) {
     qDebug() << "New connection: " << newConnection;
 }

} /* namespace ayvu */
