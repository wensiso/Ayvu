/*
 * Network.h
 *
 *  Created on: 02/08/2014
 *      Author: wendell
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <QList>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QHostAddress>
#include <QTcpSocket>

#define REQUEST_PORT 8000
#define REQUEST_PORT_STR "8000"

#define DATA_PORT 8001
#define SYNC_PORT 8002

#define BAD_REQUISITION "BAD_REQUISITION"

#define PROTO_INVITE "INVITE"
#define PROTO_ACCEPT "ACCEPT"
#define PROTO_REJECT "REJECT"
#define PROTO_CALLING "CALLING"
#define PROTO_CANCELLING "CANCELLING"
#define PROTO_FINISH "FINISH"
#define PROTO_VERSION "AYVU/1.0"
#define PROTO_AUDIO_TYPE "audio"

namespace ayvu {

class Network : public QObject
{
	Q_OBJECT

public:
	Network(QObject *parent = 0);
	static QHostAddress getValidIP();
	Q_INVOKABLE static QString getValidIPStr();
};

} /* namespace ayvu */
#endif /* NETWORK_H_ */
