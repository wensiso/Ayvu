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
        "HOST: %7:%8\r\n"
        "CALL-ID: %9\r\n"
        "\r\n";

Client::Client(QObject* parent) :
        QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_address = QHostAddress::LocalHost;

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

void Client::setAddress(QHostAddress address)
{
    if (m_socket->isOpen())
        m_socket->disconnectFromHost();
    m_address = address;
    m_socket->connectToHost(m_address, REQUEST_PORT);
    qDebug() << "Socket State: " << m_socket->state();
}

void Client::setAddress(QString address)
{
    qDebug() << "[SessionClient]: Setting address to " << address;
    if (address.toLower().compare("localhost") == 0) {
        this->setAddress(QHostAddress::LocalHost);
    } else {
        this->setAddress(QHostAddress(address));
    }
}

const QHostAddress& Client::getAddress() const
{
    return m_address;
}

const QString Client::getStrAddress() const
{
    return m_address.toString();
}

void Client::send(const QString& message)
{
    qDebug() << "[SessionClient]: Sending message to " + m_address.toString() + ": " + message;
    if (m_socket->waitForConnected()) {
        m_socket->write(QString(message + "\n").toUtf8());
        m_socket->flush();
    }
}

void Client::sendInviteMessage()
{
    QString msg = genericRequest.arg(PROTO_INVITE, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, m_address.toString(), REQUEST_PORT_STR, "12345");
    send(msg);
}

void Client::sendCallingMessage()
{
    QString msg = genericRequest.arg(PROTO_CALLING, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, m_address.toString(), REQUEST_PORT_STR, "12345");
    send(msg);
}

void Client::sendCancellingMessage()
{
    QString msg = genericRequest.arg(PROTO_CANCELLING, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, m_address.toString(), REQUEST_PORT_STR, "12345");
    send(msg);
}

void Client::sendFinishMessage()
{
    QString msg = genericRequest.arg(PROTO_FINISH, PROTO_AUDIO_TYPE, PROTO_VERSION, m_username,
            m_hostname, m_address.toString(), REQUEST_PORT_STR, "12345");
    send(msg);
}

void Client::responseReceived()
{
}

void Client::connected()
{
    qDebug() << "[SessionClient]: Connected to " + m_socket->peerAddress().toString();
}

void Client::finishedSession()
{
    qDebug() << "[SessionClient]: finishedSession";
}

} /* namespace ayvu */

