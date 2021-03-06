/*
 * client.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include <QStringList>
#include <qglobal.h>

#include <client.h>

namespace ayvu
{

extern int call_id;

const QString Client::genericRequest = "%1 %2 %3\r\n"
        PROTO_USER ": %5@%6\r\n"
        PROTO_HOST ": %7\r\n"
        PROTO_CALL_ID ": %8\r\n"
        "\r\n";

Client::Client(QSettings *settings, QObject* parent) :
        QObject(parent),
        m_settings (settings),
        state(State::getInstance())
{
    qsrand(qrand());

    m_socket = new QTcpSocket(this);
    server_address = QHostAddress::LocalHost;

    m_hostname = Network::getLocalHostname();
    my_address = Network::getValidIPStr();

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
    call_id = qrand() % ((HIGHT_RAND + 1) - LOW_RAND); //create a call_id

    QString msg = genericRequest.arg(PROTO_INVITE, PROTO_AUDIO_TYPE, PROTO_VERSION, getUsername(),
            m_hostname, Network::getValidIPStr(), QString::number(call_id));
    send(msg);
}

void Client::sendCallingMessage()
{
    qDebug() << "[Client] Sending calling...";
    QString msg = genericRequest.arg(PROTO_CALLING, PROTO_AUDIO_TYPE, PROTO_VERSION, getUsername(),
            m_hostname, my_address, QString::number(call_id));
    send(msg);
}

void Client::sendFinishMessage()
{
    QString msg = genericRequest.arg(PROTO_FINISH, PROTO_AUDIO_TYPE, PROTO_VERSION, getUsername(),
            m_hostname, my_address, QString::number(call_id));
    send(msg);
}

void Client::responseReceived()
{
    qDebug() << "[Client]: Response received!";

    QStringList message;
    while (m_socket->canReadLine()) {

        QString line = QString::fromUtf8(m_socket->readLine().trimmed());
        message.append(line);
    }
    qDebug() << "[Client]: Message: \n" << message;

    MessageType type = getMessageType(message.at(0));
    qDebug() << "Message type: " << type;

    //TODO Tratar, para cada tipo de mensagem recebida, cada estado atual.
    switch(type) {
        case ACCEPT:
            qDebug() << "[Client]: Connection accepted";
            state->setAccepted();
            sendCallingMessage();
            //TODO Starts voice here, not in QML
            state->setTalking(); //TODO Only change to TALKING state after start voice conversation
            break;
        case REJECT:
            qDebug() << "[Client]: Connection rejected";
            state->setRejected();
            state->setStopped();
            break;
        default:
            break;
    }

}

void Client::connected()
{
    qDebug() << "Client connected to " + m_socket->peerAddress().toString();
}

void Client::finishedSession()
{
    qDebug() << "[SessionClient]: finishedSession";
}

QString Client::getUsername()
{
    return m_settings->value("username").toString();
}


} /* namespace ayvu */

