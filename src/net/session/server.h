/*
 * server.h
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <QTcpServer>
#include <QString>
#include <QSettings>

#include <network.h>
#include <connection.h>
#include <state.h>

namespace ayvu {

class Connection;

class Server: public QTcpServer {
	Q_OBJECT

    Q_PROPERTY(QString clientName READ getClientName NOTIFY newClientName)
	Q_PROPERTY(QString clientAddress READ getClientAddress NOTIFY newClientAddress)

public:

	static const QString genericResponse;

	Server(QSettings *settings, QObject *parent = 0);
	void start();
	void stop();

    Q_INVOKABLE void acceptCall();
    Q_INVOKABLE void rejectCall();

    QString getClientName() const;
    QString getClientAddress() const;
    void setClientAddress(const QString& clientAddress);
    void setClientName(const QString& clientName);

    QString getUsername();
    QString getDevicename();

signals:
	void newConnection(Connection*);
	void newClientName(QString);
	void newClientAddress(QString);

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void onNewConnection(Connection*);

private:

    QSettings *m_settings;
    Connection *m_connection;
    State *state;

    QString m_clientName;
    QString m_clientAddress;

};

} /* namespace ayvu */
#endif /* SERVER_H_ */
