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
#include <QStringList>

#include "state.h"

namespace ayvu {

class Connection: public QTcpSocket {
	Q_OBJECT

public:
	Connection(QObject *parent = 0);

	bool sendAcceptMessage(const QString &message);
	bool sendRejectMessage(const QString &message);
	bool sendFinishMessage(const QString &message);

signals:
	void readyForUse();
	void newMessage(const QString &from, const QString &message);

private slots:
	void processReadyRead();

private:
	void initHandlers();
	bool sendMessage(const QString &message);

	int parseInviteMessage(QStringList &message);
	int parseCallingMessage(QStringList &message);
	int parseFinishMessage(QStringList &message);

	State *state;

	QString proto_version;
	QString call_type;
	QString client;
	QString client_host;
	int client_port;
	QString callid;

};

} /* namespace ayvu */
#endif /* CONNECTION_H_ */
