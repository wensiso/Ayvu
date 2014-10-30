/*
 * Network.cpp
 *
 *  Created on: 02/08/2014
 *      Author: wendell
 */

#include <network.h>

namespace ayvu {

Network *Network::instance = 0;

Network::Network(QObject* parent):QObject(parent)
{
    m_discovery_started = false;
    testConnection();
}

void Network::defineSettings(QSettings* settings)
{
    m_settings = settings;
}

void Network::startDeviceDiscovery()
{
    if(m_discovery_started)
        return;

    Q_ASSERT_X(m_settings, "Network::startDeviceDiscovery(QSettings*)", "m_settings parameter is null");

    QString myself = DEFAULT_USER;

    myself = m_settings->value("username").toString() + "@" + getLocalHostname();
    ssdp = new SSDP(30, myself);

    bool ok = connect(ssdp, SIGNAL(multicastError()), this, SIGNAL(discoveryError()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    ssdp->init();
    ssdp->start();
    m_discovery_started = true;


}

void Network::stopDeviceDiscovery()
{
    ssdp->stop();
    disconnect(ssdp, SIGNAL(multicastError()), this, SIGNAL(discoveryError()));
    delete ssdp;
    m_discovery_started = false;
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

QString Network::getLocalHostname()
{
    return QHostInfo::localHostName();
}

SSDP* Network::getSSDP() const
{
    return ssdp;
}

} /* namespace ayvu */
