/*
 * Network.cpp
 *
 *  Created on: 02/08/2014
 *      Author: wendell
 */

#include <network.h>

namespace ayvu {

MessageType getMessageType(const QString &message) {
    if (message.startsWith(PROTO_INVITE))
        return INVITE;
    if (message.startsWith(PROTO_ACCEPT))
        return ACCEPT;
    if (message.startsWith(PROTO_REJECT))
        return REJECT;
    if(message.startsWith(PROTO_CALLING))
        return CALLING;
    if(message.startsWith(PROTO_CANCELLING))
        return CANCELLING;
    if(message.startsWith(PROTO_FINISH))
        return FINISH;
    return ERROR;
}

Network::Network(QObject* parent):QObject(parent) {
}

QHostAddress Network::getValidIP()
{
	foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces())
	{
		foreach (const QHostAddress &address, interface.allAddresses())
		{
			if (address.protocol() == QAbstractSocket::IPv4Protocol
					&& address != QHostAddress(QHostAddress::LocalHost))
				return address;
		}
	}
	return QHostAddress::LocalHost;
}

QString Network::getValidIPStr()
{
	return  getValidIP().toString();
}

QString Network::getHostname()
{
    return HOSTNAME;
}

} /* namespace ayvu */

