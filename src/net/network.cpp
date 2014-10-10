/*
 * Network.cpp
 *
 *  Created on: 02/08/2014
 *      Author: wendell
 */

#include <network.h>

namespace ayvu {

Network *Network::instance = 0;

Network::Network(QSettings *settings, QObject* parent):QObject(parent), m_settings(settings) {

    devices = new QList<QString>();

    QString myself = m_settings->value("username").toString() + "@" + getHostname();
    ssdp = new SSDP(30, myself);

    Q_ASSERT(connect(ssdp, SIGNAL(newDeviceFound(QString)), this, SLOT(addDevice(QString))));
    Q_ASSERT(connect(ssdp, SIGNAL(deviceAlive(QString)), this, SLOT(deviceAlive(QString))));
    Q_ASSERT(connect(ssdp, SIGNAL(byebyeReceived(QString)), this, SLOT(removeDevice(QString))));

    Q_ASSERT(connect(ssdp, SIGNAL(multicastError()), this, SIGNAL(discoveryError())));

    testConnection();
}

void Network::startDeviceDiscovery()
{
    if(testConnection())
    {
        ssdp->init();
        ssdp->start();
    }
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

bool Network::testConnection()
{
    QNetworkConfigurationManager mgr;
    QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(
            QNetworkConfiguration::Active);

    m_connected = (activeConfigs.count() > 0) ? mgr.isOnline() : false;
    return m_connected;
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

