#ifndef DATASENDER_H_
#define DATASENDER_H_

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <QDateTime>

#include <message.h>

namespace ayvu {

class DataSender: public QObject {
	Q_OBJECT
public:

	static DataSender *getInstance(QObject *parent=0) {
		if (!instance)
			instance = new DataSender(parent);
		return instance;
	}

	void setAddress(QHostAddress address);

	Q_INVOKABLE void setAddress(QString address);

	const QHostAddress& getAddress() const;
	int writeMessage(QByteArray &datagram);

private:
	static DataSender *instance;  //Singleton
	DataSender(QObject *parent=0);

	static qint64 seq;

	QUdpSocket *m_udpSender;
	QHostAddress m_address;
};
}

#endif /* DATASENDER_H_ */
