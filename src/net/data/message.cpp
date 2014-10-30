/*
 * Message.cpp
 *
 *  Created on: 07/11/2013
 *      Author: Wendell
 */

#include <message.h>

namespace ayvu {

Message::Message() {
	m_header.timestamp = 0;
	m_header.sequence = 0;
	m_data = new QByteArray();
	m_receive_timestamp = 0;
}

Message::Message(QByteArray& data, qint64 seq) {

	m_header.timestamp = QDateTime::currentMSecsSinceEpoch();

	m_header.sequence = seq;

	m_data = new QByteArray(data);
	m_receive_timestamp = 0;
}

void Message::createFromReceivedDatagram(QByteArray *datagram) {

	m_receive_timestamp = QDateTime::currentMSecsSinceEpoch();

	int headerSize = 2*sizeof(qint64);

	QByteArray myDatagram = *datagram;
	QByteArray header = myDatagram.left(headerSize);

	char* char_ts = header.left(sizeof(qint64)).data();
	memcpy(&m_header.timestamp, char_ts, sizeof(qint64));

	char *char_seq = header.right(sizeof(qint64)).data();
	memcpy(&m_header.sequence, char_seq, sizeof(qint64));

	myDatagram.remove(0, headerSize);
	m_data = new QByteArray(myDatagram);
}

QByteArray Message::createDatagram() {
	QByteArray message;

	char char_ts[sizeof(qint64)];
	memcpy(char_ts, &m_header.timestamp, sizeof(qint64));
	message.append(char_ts, sizeof(qint64));

	char char_seq[sizeof(qint64)];
	memcpy(char_seq, &m_header.sequence, sizeof(qint64));
	message.append(char_seq, sizeof(qint64));

	message.append(*m_data);
	return message;
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

 qint64 Message::getTimeStamp() const {
	return m_header.timestamp;
}

}
