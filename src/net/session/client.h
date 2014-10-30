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
#include <QSettings>

#include <network.h>
#include <state.h>

#define LOW_RAND 1000
#define HIGHT_RAND 9999

namespace ayvu {

class Client : public QObject {
    Q_OBJECT
public:

    static const QString genericRequest;

    Client(QSettings *settings, QObject *parent=0);

    void setServerAddress(QHostAddress address);
    const QHostAddress& getServerAddress() const;
    Q_INVOKABLE void setServerAddress(QString address);
    Q_INVOKABLE const QString getStrServerAddress() const;

    Q_INVOKABLE void sendInviteMessage();
    Q_INVOKABLE void sendCallingMessage();
    Q_INVOKABLE void sendFinishMessage();

public slots:
    void finishedSession();

private slots:
    void responseReceived();
    void connected();

private:
    void initHandlers();
    void send(const QString &);
    QString getUsername();
    QString getDevicename();

    QTcpSocket *m_socket;
    QHostAddress server_address;
    QSettings *m_settings;

    State *state;

    QString m_hostname;
    QString my_address;

};

} /* namespace ayvu */
#endif /* CLIENT_H_ */
