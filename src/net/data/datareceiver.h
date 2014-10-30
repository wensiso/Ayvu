/*
 * AudioReceiver.h
 *
 *  Created on: 13/10/2013
 *      Author: wendell
 */

#ifndef DATARECEIVER_H_
#define DATARECEIVER_H_

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QHostAddress>

#include <audiopcm.h>
#include <message.h>
#include <datasender.h>
#include <network.h>

namespace ayvu {

/**
 * Class to receive audio data from network
 */
class DataReceiver: public QObject {
	Q_OBJECT
public:

	static DataReceiver *getInstance(QObject *parent=0) {
		if (!instance)
			instance = new DataReceiver(parent);
		return instance;
	}

	void start();
	void stop();

private slots:
	void messageReceived();

private:
	static DataReceiver *instance;  //Singleton
	DataReceiver(QObject *parent=0);

	QUdpSocket *m_udpListener;
	QByteArray *m_datagram;

};
}

#endif /* DATARECEIVER_H_ */
