/*
 * connection.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include <connection.h>
#include <network.h>

namespace ayvu {

Connection::Connection(QObject *parent)
: QTcpSocket(parent)
{
    qDebug() << "[SERVER]: New connection...";
    appinfo = AppInfo::getInstance();
    state = State::getInstance();
    initHandlers();
}

void Connection::initHandlers()
{
    int r = connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    Q_ASSERT(r);
}

void Connection::processReadyRead()
{
    QStringList message;
    QString from = peerAddress().toString();
    qDebug() << "[SERVER]: Connection with " << from;

    while (canReadLine()) {

        QString line = QString::fromUtf8(readLine().trimmed());
        message.append(line);
    }
    qDebug() << "[SERVER]: Message: \n" << message;

    MessageType type = getMessageType(message.at(0));
    qDebug() << "Message type: " << type;
    qDebug() << "My state: " << state->getStateStr();

    //TODO Tratar, para cada tipo de mensagem recebida, cada estado atual.
    switch(type) {
        case INVITE:
            if(state->isStopped()) {
                parseInviteMessage(message);
            } else {
                sendRejectMessage(PROTO_RCAUSE_BUSY);
            }
            break;
        case CALLING:
            break;
        case FINISH:
            state->setStopped();
            break;
        default:
            break;
    }
}

int Connection::parseInviteMessage(QStringList& message)
{
    qDebug() << "[SERVER]: Parsing INVITE message";
    state->setIncomming();
    return 0;
}

int Connection::parseCallingMessage(QStringList& message)
{
    return 0;
}

int Connection::parseFinishMessage(QStringList& message)
{
    return 0;
}

bool Connection::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return false;

    QByteArray msg = message.toUtf8();
    QByteArray data = msg;
    return write(data) == data.size();
}

bool Connection::sendAcceptMessage()
{
    qDebug() << "[SERVER]: Accepting connection";
    QString media_host = Network::getValidIPStr() + ":" + QString::number(DATA_PORT);

    QString msg = Server::genericResponse.arg(PROTO_ACCEPT, PROTO_AUDIO_TYPE, PROTO_VERSION, appinfo->getUsername(),
            Network::getHostname(), media_host, "12345");
    return sendMessage(msg);
}

bool Connection::sendRejectMessage(const QString &cause)
{
    qDebug() << "[SERVER]: Rejecting connection: " << cause;
    QString msg = Server::genericResponse.arg(PROTO_REJECT, PROTO_AUDIO_TYPE, PROTO_VERSION, appinfo->getUsername(),
            Network::getHostname(), Network::getValidIPStr(), "12345", cause);
    return sendMessage(msg);
}

bool Connection::sendFinishMessage(const QString &message)
{
    QString msg(PROTO_FINISH);
    msg += " " + message;
    return sendMessage(msg);
}

} /* namespace ayvu */
