/*
 * client.h
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

#include "../network.h"

namespace ayvu {

class Client : public QObject {
    Q_OBJECT
public:

    static const QString genericRequest;

    Client(QObject *parent=0);

    void setAddress(QHostAddress address);
    const QHostAddress& getAddress() const;
    Q_INVOKABLE void setAddress(QString address);
    Q_INVOKABLE const QString getStrAddress() const;

    Q_INVOKABLE void sendInviteMessage();
    Q_INVOKABLE void sendCallingMessage();
    Q_INVOKABLE void sendCancellingMessage();
    Q_INVOKABLE void sendFinishMessage();

public slots:
    void finishedSession();

private slots:
    void responseReceived();
    void connected();

private:
    void initHandlers();
    void send(const QString &);

    QTcpSocket *m_socket;
    QHostAddress m_address;

    QString m_username;
    QString m_hostname;

};

} /* namespace ayvu */
#endif /* CLIENT_H_ */
