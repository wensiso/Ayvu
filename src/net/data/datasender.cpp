#include <datasender.h>

#include <network.h>

namespace ayvu {

DataSender *DataSender::instance = 0;
qint64 DataSender::seq = 0;

DataSender::DataSender(QObject *parent) : QObject(parent)
{
	this->m_udpSender = new QUdpSocket(this);
	this->m_address = QHostAddress::LocalHost;
}

void DataSender::setAddress(QHostAddress address) {
    qDebug() << "[DataSender] New destiny address: " << address.toString();
	this->m_address = address;
}

void DataSender::setAddress(QString address) {
	if (address.toLower().compare("localhost") == 0) {
		this->setAddress(QHostAddress::LocalHost);
	} else {
		this->setAddress(QHostAddress(address));
	}
}

const QHostAddress& DataSender::getAddress() const {
	return m_address;
}

/**
 * Send a message created from a datagram
 */
int DataSender::writeMessage(QByteArray &datagram) {
	int ret;

	++seq; //Overflow will be a problem in 2032...

	Message packet(Message::NORMAL, seq, datagram);
	QByteArray message = packet.createDatagram();

	ret = m_udpSender->writeDatagram(message.data(), message.size(),
			this->m_address, DATA_PORT);

	if (ret < 0) {
		--seq;
		qWarning() << "Error: message wasn't sent!";
	}
	return ret;
}

/**
 * Send a pure datagram (to reports...)
 */
int DataSender::writeDatagram(QByteArray &datagram) {
	int ret;

    qDebug() << "[DataSender] Sending report to " << m_udpSender->localAddress().toString();


	ret = m_udpSender->writeDatagram(datagram.data(), datagram.size(),
			this->m_address, DATA_PORT);

	if (ret < 0) {
		qWarning() << "[DataSender] Error: datagram wasn't sent!";
	}
	return ret;
}

}
