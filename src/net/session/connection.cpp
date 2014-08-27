/*
 * connection.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include <QStringList>

#include "connection.h"

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

bool Connection::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return false;

    QByteArray msg = message.toUtf8();
    QByteArray data = msg;
    return write(data) == data.size();
}

bool Connection::sendCallMessage(const QString &message)
{
    QString msg = "CALL " + message;
    return sendMessage(msg);
}

bool Connection::sendBusyMessage(const QString &message)
{
    QString msg = "BUSY " + message;
    return sendMessage(msg);
}

bool Connection::sendFinishMessage(const QString &message)
{
    QString msg = "FINISH " + message;
    return sendMessage(msg);
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
                // Tratar incomming
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

Connection::MessageType Connection::getMessageType(const QString& message)
{
    if (message.startsWith("INVITE"))
        return INVITE;
    if(message.startsWith("CALLING"))
        return CALLING;
    if(message.startsWith("FINISH"))
        return FINISH;
    return ERROR;
}

} /* namespace ayvu */
