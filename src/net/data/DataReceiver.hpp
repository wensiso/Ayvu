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
#include <QDir>

#define LOG_DIR "shared/documents/wt/"
#define LOG_FILE "log-"

namespace ayvu {

/**
 * Class to receive audio data from network
 */
class DataReceiver: public QObject {
	Q_OBJECT
public:

	static DataReceiver *getInstance() {
		if (!instance)
			instance = new DataReceiver();
		return instance;
	}

	void start();
	void stop();

public slots:
	void setLoggingPercent(double);

private slots:
	void messageReceived();

private:
	static DataReceiver *instance;  //Singleton
	DataReceiver();

	void createLogFile();
	void printLatency(qint64, qint64);
	void writeLatency(qint64, qint64);

	QUdpSocket *m_udpListener;
	QByteArray *m_datagram;

	QDir *m_logdir;
	QFile *m_logfile;

	bool m_logfileCreated;
	double m_loggingPercent; //Default is 0 (log off)

};
}

#endif /* DATARECEIVER_H_ */
