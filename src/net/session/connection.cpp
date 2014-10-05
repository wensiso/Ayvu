/*
 * connection.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include <connection.h>
#include <network.h>

#include <QString>

namespace ayvu {

Connection::Connection(QObject *parent)
: QTcpSocket(parent)
{
    qDebug() << "[SERVER]: New connection...";
    appinfo = AppInfo::getInstance();
    state = State::getInstance();
    server = dynamic_cast<Server*> (parent);

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
    QHash<QString, QString> request;
    int i=0;

    QString from = peerAddress().toString();
    qDebug() << "[SERVER]: Receiving connection from " << from;

    while (canReadLine()) {
        QString line = QString::fromUtf8(readLine().trimmed());
        if(i && !line.isEmpty()) {  //pula a primeira e a ultima linha
            QStringList token = line.remove(' ').split(':', QString::SkipEmptyParts);
            request.insert(token.at(0), token.at(1));
        }
        message.append(line);
        ++i;
    }

    MessageType type = getMessageType(message.at(0));
    qDebug() << "Message type: " << type;
    qDebug() << "Request: \n" << request;
    qDebug() << "My state: " << state->getStateStr();

    //TODO Tratar, para cada tipo de mensagem recebida, cada estado atual.
    switch(type) {
        case INVITE:
            if(state->isStopped()) {
                parseInviteRequest(request);
            } else {
                sendRejectMessage(PROTO_RCAUSE_BUSY);
            }
            break;
        case CALLING:
            parseCallingRequest(request);
            break;
        case FINISH:
            state->setStopped();
            break;
        default:
            break;
    }
}

int Connection::parseInviteRequest(QHash<QString, QString>& request)
{
    qDebug() << "[SERVER]: Parsing INVITE request";

    QString username = request.find(PROTO_USER).value();
    QString host = request.find(PROTO_HOST).value();

    qDebug() << "[SERVER]: Connected with " << username << " from " << host;

    server->setClientName(username);
    server->setClientAddress(host);
    state->setIncomming();
    return 0;
}

int Connection::parseCallingRequest(QHash<QString, QString>& request)
{
    //TODO Parse calling message
    //TODO start void here
    return 0;
}

int Connection::parseFinishRequest(QHash<QString, QString>& request)
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
