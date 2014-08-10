/*
 * server.h
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <QTcpServer>

#include "../network.h"
#include "connection.h"

namespace ayvu {

class Server: public QTcpServer {
	Q_OBJECT

public:
	Server(QObject *parent = 0);
	void start();

signals:
	void newConnection(Connection*);

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void onNewConnection(Connection*);


private:
    Connection *m_connection;

};

} /* namespace ayvu */
#endif /* SERVER_H_ */
