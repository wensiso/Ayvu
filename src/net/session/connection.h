/*
 * connection.h
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <QTcpSocket>
#include <QHostAddress>

#include "state.h"

namespace ayvu {

class Connection: public QTcpSocket {
	Q_OBJECT

	enum MessageType {
	    ERROR = -1,
	    CALL,
	    BUSY,
	    FINISH
	};

public:
	Connection(QObject *parent = 0);

	bool sendCallMessage(const QString &message);
	bool sendBusyMessage(const QString &message);
	bool sendFinishMessage(const QString &message);

signals:
	void readyForUse();
	void newMessage(const QString &from, const QString &message);

private slots:
	void processReadyRead();

private:
	void initHandlers();
	bool sendMessage(const QString &message);
	MessageType getMessageType(const QString &message);

	State *state;

};

} /* namespace ayvu */
#endif /* CONNECTION_H_ */
