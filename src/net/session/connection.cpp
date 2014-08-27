/*
 * connection.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include "connection.h"
#include "network.h"

namespace ayvu {

Connection::Connection(QObject *parent)
: QTcpSocket(parent)
{
    qDebug() << "[SERVER]: New connection...";
    state = State::getInstance();
    initHandlers();
}

void Connection::initHandlers()
{
    int r;
    r = connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
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

    //TODO Tratar, para cada tipo de mensagem recebida, cada estado atual.
    switch(type) {
        case INVITE:
//            if(state->isStopped())
            {
                state->setIncomming();
                parseInviteMessage(message);
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

bool Connection::sendAcceptMessage(const QString &message)
{
    QString msg(PROTO_ACCEPT);
    msg += " " + message;
    return sendMessage(msg);
}

bool Connection::sendRejectMessage(const QString &message)
{
    QString msg(PROTO_REJECT);
    msg += " " + message;
    return sendMessage(msg);
}

bool Connection::sendFinishMessage(const QString &message)
{
    QString msg(PROTO_FINISH);
    msg += " " + message;
    return sendMessage(msg);
}

} /* namespace ayvu */
