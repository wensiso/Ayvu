/*
 * Network.cpp
 *
 *  Created on: 02/08/2014
 *      Author: wendell
 */

#include "network.h"

namespace ayvu {

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

} /* namespace ayvu */
