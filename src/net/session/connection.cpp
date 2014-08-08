/*
 * connection.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include "connection.h"

namespace ayvu {

Connection::Connection(QObject *parent)
: QTcpSocket(parent)
{
    state = State::getInstance();
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
    QString from = peerAddress().toString();
    qDebug() << "[SERVER]: Connection::processReadyRead() from " << from;

    while (canReadLine()) {
        QString line = QString::fromUtf8(readLine().trimmed());
        qDebug() << "[SERVER]: Message: " << line;

        MessageType type = getMessageType(line);

        switch(type) {
            case CALL:
                if(state->isStopped())
                {
                    state->setIncomming();
                }
                break;
            case BUSY:
                break;
            case FINISH:
                break;
            default:
                break;
        }
    }
}

Connection::MessageType Connection::getMessageType(const QString& message)
{
    if (message.startsWith("CALL"))
        return CALL;
    if(message.startsWith("BUSY"))
        return BUSY;
    if(message.startsWith("FINISH"))
        return FINISH;
    return ERROR;
}

} /* namespace ayvu */
