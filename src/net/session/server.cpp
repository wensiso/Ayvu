/*
 * server.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include <server.h>

namespace ayvu {

const QString Server::genericResponse = "%1 %2 %3\r\n"
        PROTO_USER ": %5@%6\r\n"
        PROTO_HOST ": %7\r\n"
        PROTO_CALL_ID ": %8\r\n"
        PROTO_CAUSE ": %9"
        "\r\n";

Server::Server(QSettings *settings, QObject *parent)
     : QTcpServer(parent)
 {
    m_connection = 0;
    state = State::getInstance();
    m_clientName = "None";
    m_clientAddress = "None";

    m_settings = settings;

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

void Server::stop()
{
    if(this->isListening())
        this->close();
}

 void Server::incomingConnection(int socketDescriptor)
 {
     m_connection = new Connection(this);
     m_connection->setSocketDescriptor(socketDescriptor);
     qDebug() << "[SessionServer]: Emiting event: newConnection";
     emit newConnection(m_connection);
 }

void Server::acceptCall()
{
    m_connection->sendAcceptMessage();
    state->setTalking(); //TODO Active this state only after voice send start
}

void Server::rejectCall()
{
    m_connection->sendRejectMessage(PROTO_RCAUSE_BUSY);
    state->setStopped();
}

 void Server::onNewConnection(Connection* newConnection) {
     qDebug() << "New connection: " << newConnection;
 }

 void Server::setClientAddress(const QString& clientAddress)
 {
     m_clientAddress = clientAddress;
     emit newClientAddress(clientAddress);
 }

 void Server::setClientName(const QString& clientName)
 {
     m_clientName = clientName;
     emit newClientName(clientName);
 }

QString Server::getClientName() const
{
    return m_clientName;
}

QString Server::getClientAddress() const
{
    return m_clientAddress;
}

QString Server::getUsername()
{
    return m_settings->value("username").toString();
}

} /* namespace ayvu */


