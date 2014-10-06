/*
 * Message.cpp
 *
 *  Created on: 07/11/2013
 *      Author: Wendell
 */

#include <message.h>

namespace ayvu {

extern qint64 clock_skew;

Message::Message() {
	m_header.type = NORMAL;
	m_header.timestamp = 0;
	m_header.sequence = 0;
	m_data = new QByteArray();
	m_receive_timestamp = 0;
}

Message::Message(char type, qint64 seq, QByteArray& data) {

	m_header.type = type;

	m_header.timestamp = QDateTime::currentMSecsSinceEpoch();
	m_header.timestamp += clock_skew;

	m_header.sequence = seq;

	m_data = new QByteArray(data);
	m_receive_timestamp = 0;
}

void Message::createFromReceivedDatagram(QByteArray *datagram) {

	m_receive_timestamp = QDateTime::currentMSecsSinceEpoch();

	int headerSize = sizeof(char) + 2*sizeof(qint64);

	QByteArray myDatagram = *datagram;
	QByteArray header = myDatagram.left(headerSize);

	m_header.type = header.at(0);
	header.remove(0, 1);

	char* char_ts = header.left(sizeof(qint64)).data();
	memcpy(&m_header.timestamp, char_ts, sizeof(qint64));

	char *char_seq = header.right(sizeof(qint64)).data();
	memcpy(&m_header.sequence, char_seq, sizeof(qint64));

	myDatagram.remove(0, headerSize);
	m_data = new QByteArray(myDatagram);
}

QByteArray Message::createDatagram() {
	QByteArray message;
	message.append(m_header.type);

	char char_ts[sizeof(qint64)];
	memcpy(char_ts, &m_header.timestamp, sizeof(qint64));
	message.append(char_ts, sizeof(qint64));

	char char_seq[sizeof(qint64)];
	memcpy(char_seq, &m_header.sequence, sizeof(qint64));
	message.append(char_seq, sizeof(qint64));

	message.append(*m_data);
	return message;
}

/**
 * Return the latency of package based from m_header.timestamp
 * For tests only.
 */
qint64 Message::getLatency() {

	//If i created this message, the latency is 0
	if(!m_receive_timestamp)
		return 0;

	if(m_header.type == Message::CONTROL) {
		return (m_receive_timestamp - m_header.timestamp)/2;
	} else {
		//Latency corrected
			//If i'm a time server, clock_skew == 0
		//If methos do not works, delete
//		return (m_receive_timestamp + clock_skew - m_header.timestamp);
		qWarning() << "[Message]: Only control messages provides accurate latency";
		return 0;
	}
}

//Getters and Setters
QByteArray* Message::getData() const {
	return m_data;
}

void Message::setData(QByteArray* data) {
	m_data = data;
}

void Message::setHeader(Message::Header header) {
	m_header = header;
}

qint64 Message::getSequence() const {
	return m_header.sequence;
}

void Message::setSequence(const qint64& sequence) {
	m_header.sequence = sequence;
}

char Message::getType() const {
	return m_header.type;
}

void Message::setType(char type) {
	m_header.type = type;
}

 qint64 Message::getTimeStamp() const {
	return m_header.timestamp;
}

}
