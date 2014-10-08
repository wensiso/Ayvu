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

#include <ssdp.h>

//TODO Pegar hostname do usuario
#define HOSTNAME "BlackberryZ10"

#define REQUEST_PORT 8000
#define REQUEST_PORT_STR "8000"

#define DATA_PORT 8001
#define SYNC_PORT 8002

#define BAD_REQUISITION "BAD_REQUISITION"

#define PROTO_INVITE "INVITE"
#define PROTO_ACCEPT "ACCEPT"
#define PROTO_REJECT "REJECT"
#define PROTO_CALLING "CALLING"
#define PROTO_FINISH "FINISH"
#define PROTO_VERSION "AYVU/1.0"
#define PROTO_AUDIO_TYPE "audio"

#define PROTO_USER "USER"
#define PROTO_HOST "HOST"
#define PROTO_CALL_ID "CALL-ID"
#define PROTO_CAUSE "CAUSE"

#define PROTO_RCAUSE_CALLING PROTO_CALLING
#define PROTO_RCAUSE_TALKING "Talking"
#define PROTO_RCAUSE_INCOMMING "Incomming"
#define PROTO_RCAUSE_BUSY "Busy"


namespace ayvu {

enum MessageType {
    ERROR = -1,
    INVITE,
    ACCEPT,
    REJECT,
    CALLING,
    CANCELLING,
    FINISH
};

MessageType getMessageType(const QString &);

class SSDP;

class Network : public QObject
{
	Q_OBJECT

public:

	static Network *getInstance(QObject *parent=0)
	{
	    if (!instance)
	        instance = new Network(parent);
	    return instance;
	}
	static QHostAddress getValidIP();
	Q_INVOKABLE static QString getValidIPStr();
	Q_INVOKABLE static QString getHostname();

	void startDeviceDiscovery();
	void stopDeviceDiscovery();

signals:
    void networkError();
    void devicesUpdated(QList<QString>*);

private slots:
    void addDevice(QString);
    void deviceAlive(QString);
    void removeDevice(QString);

private:
    static Network *instance;
    Network(QObject *parent = 0);


    SSDP *ssdp;
    QList<QString> *devices;

};

} /* namespace ayvu */
#endif /* NETWORK_H_ */
