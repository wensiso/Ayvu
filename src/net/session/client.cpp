/*
 * client.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include "client.h"

namespace ayvu
{

const QString Client::genericRequest = "%1 %2 %3\r\n"
        "USER: %5@%6\r\n"
        "HOST: %7\r\n"
        "CALL-ID: %8\r\n"
        "\r\n";

Client::Client(QObject* parent) :
        QObject(parent)
{
    m_socket = new QTcpSocket(this);
    server_address = QHostAddress::LocalHost;

    my_address = Network::getValidIP();

    m_username = "wendell";
    m_hostname = "blackberryZ10";

    this->initHandlers();
}

void Client::initHandlers()
{
    int r = connect(m_socket, SIGNAL(readyRead()), this, SLOT(responseReceived()));
    int s = connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    Q_ASSERT(r);
    Q_ASSERT(s);
}

void Client::setServerAddress(QHostAddress address)
{
    if (m_socket->isOpen())
        m_socket->disconnectFromHost();
    server_address = address;
    m_socket->connectToHost(server_address, REQUEST_PORT);
    qDebug() << "Socket State: " << m_socket->state();
}

void Client::setServerAddress(QString address)
{
    qDebug() << "Setting server address to " << address;
    if (address.toLower().compare("localhost") == 0) {
        this->setServerAddress(QHostAddress::LocalHost);
    } else {
        this->setServerAddress(QHostAddress(address));
    }
}

const QHostAddress& Client::getServerAddress() const
{
    return server_address;
}

const QString Client::getStrServerAddress() const
{
    return server_address.toString();
}

void Client::send(const QString& message)
{
    qDebug() << "Sending message to " + server_address.toString() + ": \r\n" + message;
    if (m_socket->waitForConnected()) {
        m_socket->write(QString(message).toUtf8());
        m_socket->flush();
    }
}

void Client::sendInviteMessage()
{
    QString msg = genericRequest.arg(PROTO_INVITE, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, my_address.toString(), "12345");
    send(msg);
}

void Client::sendCallingMessage()
{
    QString msg = genericRequest.arg(PROTO_CALLING, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, my_address.toString(), "12345");
    send(msg);
}

void Client::sendCancellingMessage()
{
    QString msg = genericRequest.arg(PROTO_CANCELLING, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, my_address.toString(), "12345");
    send(msg);
}

void Client::sendFinishMessage()
{
    QString msg = genericRequest.arg(PROTO_FINISH, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, my_address.toString(), "12345");
    send(msg);
}

void Client::responseReceived()
{
}

void Client::connected()
{
    qDebug() << "Client connected to " + m_socket->peerAddress().toString();
}

void Client::finishedSession()
{
    qDebug() << "[SessionClient]: finishedSession";
}

} /* namespace ayvu */

