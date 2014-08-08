/*
 * server.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include "server.h"

namespace ayvu {

Server::Server(QObject *parent)
     : QTcpServer(parent)
 {
     listen(QHostAddress::Any);
 }

 void Server::incomingConnection(int socketDescriptor)
 {
     Connection *connection = new Connection(this);
     connection->setSocketDescriptor(socketDescriptor);
     emit newConnection(connection);
 }

} /* namespace ayvu */
