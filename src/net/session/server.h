/*
 * server.h
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <QTcpServer>

#include "connection.h"

namespace ayvu {

class Server: public QTcpServer {
	Q_OBJECT

public:
	Server(QObject *parent = 0);

	signals:
	void newConnection(Connection *connection);

protected:
	void incomingConnection(int socketDescriptor);
};

} /* namespace ayvu */
#endif /* SERVER_H_ */
