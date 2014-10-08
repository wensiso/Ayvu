/*
 * Network.cpp
 *
 *  Created on: 02/08/2014
 *      Author: wendell
 */

#include <network.h>

namespace ayvu {

Network *Network::instance = 0;

Network::Network(QObject* parent):QObject(parent) {
    devices = new QList<QString>();

    ssdp = new SSDP(30);

    Q_ASSERT(connect(ssdp, SIGNAL(newDeviceFound(QString)), this, SLOT(addDevice(QString))));
    Q_ASSERT(connect(ssdp, SIGNAL(deviceAlive(QString)), this, SLOT(deviceAlive(QString))));
    Q_ASSERT(connect(ssdp, SIGNAL(byebyeReceived(QString)), this, SLOT(removeDevice(QString))));

    Q_ASSERT(connect(ssdp, SIGNAL(multicastError()), this, SIGNAL(networkError())));
}

void Network::startDeviceDiscovery()
{
    ssdp->init();
    ssdp->start();
}

void Network::stopDeviceDiscovery()
{
    ssdp->stop();
}


void Network::addDevice(QString device)
{
    devices->append(device);
}

void Network::deviceAlive(QString device)
{
    //TODO Tratar alive
    devices->append(device);
}

void Network::removeDevice(QString device)
{
    devices->removeOne(device);
}

MessageType getMessageType(const QString &message) {
    if (message.startsWith(PROTO_INVITE))
        return INVITE;
    if (message.startsWith(PROTO_ACCEPT))
        return ACCEPT;
    if (message.startsWith(PROTO_REJECT))
        return REJECT;
    if (message.startsWith(PROTO_CALLING))
            return CALLING;
    if(message.startsWith(PROTO_FINISH))
        return FINISH;
    return ERROR;
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

