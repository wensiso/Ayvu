/*
 * server.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include <server.h>

namespace ayvu {

const QString Server::genericResponse = "%1 %2 %3\r\n"
        "USER: %5@%6\r\n"
        "HOST: %7\r\n"
        "CALL-ID: %8\r\n"
        "CAUSE: %9"
        "\r\n";

Server::Server(QObject *parent)
     : QTcpServer(parent)
 {
    m_connection = 0;
    int c = connect(this, SIGNAL(newConnection(Connection*)), this, SLOT(onNewConnection(Connection*)));
    Q_ASSERT(c);
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
