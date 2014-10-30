#include <datareceiver.h>

namespace ayvu {

DataReceiver *DataReceiver::instance = 0;

DataReceiver::DataReceiver(QObject *parent) : QObject(parent)
{
	m_udpListener = new QUdpSocket(this);
	m_datagram = new QByteArray();
}

void DataReceiver::start() {
	QHostAddress host = Network::getValidIP();

	m_udpListener->bind(host, DATA_PORT);

	bool ret = connect(m_udpListener, SIGNAL(readyRead()), this,
			SLOT(messageReceived()));

	if (ret)
		qDebug() << "Receiving audio data on " + host.toString() + ":"
						+ QString::number(DATA_PORT);

	Q_ASSERT_X(ret, "DataReceiver::start" , QString("Socket bind failure on " + host.toString() + ":"
            + QString::number(DATA_PORT)).toAscii());
}

void DataReceiver::stop() {
	disconnect(m_udpListener, SIGNAL(readyRead()), this,
			SLOT(messageReceived()));
	m_udpListener->close();
}

/**
 * Slot for datagram received.
 */
void DataReceiver::messageReceived() {

	while (m_udpListener->hasPendingDatagrams()) {

		m_datagram->resize(m_udpListener->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		m_udpListener->readDatagram(m_datagram->data(), m_datagram->size(),
				&sender, &senderPort);
	}

	Message message;
	message.createFromReceivedDatagram(m_datagram);

	AudioPCM::writeDatagramToCircularBuffer(message.getData());
	AudioPCM::setCaptureReady(true);

}

}


