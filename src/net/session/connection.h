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

#include <server.h>
#include <state.h>

namespace ayvu {

class Server;

class Connection: public QTcpSocket {
	Q_OBJECT

public:
	Connection(QObject *parent = 0);

	bool sendAcceptMessage();
	bool sendRejectMessage(const QString &cause);
	bool sendFinishMessage(const QString &message);

signals:
	void readyForUse();
	void newMessage(const QString &from, const QString &message);

private slots:
	void processReadyRead();

private:
	void initHandlers();
	bool sendMessage(const QString &message);

	int parseInviteRequest(QHash<QString, QString> &request);
	int parseCallingRequest(QHash<QString, QString> &request);
	int parseFinishRequest(QHash<QString, QString> &request);

	State *state;
	Server *server;

	QString proto_version;
	QString call_type;
	QString client;
	QString client_host;
	int client_port;
	QString callid;

};

} /* namespace ayvu */
#endif /* CONNECTION_H_ */
