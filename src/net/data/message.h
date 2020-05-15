/*
 * Message.hpp
 *
 *  Created on: 07/11/2013
 *      Author: Wendell
 */

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

/**
 * Message: [[TIME_STAMP (8 bytes)][SEQ_NUMBER (8 bytes)][DATA (640 bytes)]
 *          [           HEADER (16 bytes)               ][DATA (640 bytes)]
 */

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QBitArray>

namespace ayvu {

class Message {
public:

	struct Header {
		qint64 timestamp; //8 bytes
		qint64 sequence;  //8 bytes
	};

	Message();
	Message(QByteArray& data, qint64 seq=0);

	//Create a Message object from a received datagram
	void createFromReceivedDatagram(QByteArray *datagram);

	//Create a datagram from a Message
	QByteArray createDatagram();

	//Getters and Setters
	QByteArray* getData() const;
	void setData(QByteArray* data);
	void setHeader(struct Header header);
	qint64 getSequence() const;
	void setSequence(const qint64& sequence);
	qint64 getTimeStamp() const;

private:
	struct Header m_header;
	QByteArray *m_data;

	/**
	 * Timestamp when datagram was received.
	 * If message i created this message, m_receive_time=0
	 * Else if message i received this message:
	 *      m_receiver_time = QDateTime::currentMSecsSinceEpoch()
	 */
	qint64 m_receive_timestamp;

};
}

#endif /* MESSAGE_HPP_ */
