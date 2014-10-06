/*
 * ssdp.h
 *
 *  Created on: 06/10/2014
 *      Author: wendell
 */

#ifndef SSDP_H_
#define SSDP_H_

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QList>
#include <QHostAddress>
#include <QStringList>
#include <QMap>
#include <QMapIterator>

#include <network.h>
#include "ssdpprotocol.h"

namespace ayvu {

class SSDP: public QObject {
Q_OBJECT

public:
    explicit SSDP(int interval = 1, QObject *parent = 0);
    ~SSDP();
    void start();
    void stop();
    void doubleDiscover(const QString &type = QString("ayvu:all"),
            const QString &mx = QString("1"), const QString &userAgent =
                    QString("Ayvu Messenger/1.0"));

    QMap<QString, QString> getMapFromMessage(QString message);

private:

    void init();
    void parseMessage(const QString &);
    QString *getValue(QMapIterator<QString, QString> &, QString);

    QTimer *discoverTimer;
    QUdpSocket *udpSocket;
    int interval;

private slots:
    void datagramReceived();

public slots:
    void discover(const QString &type = QString("ayvu:all"), const QString &mx =
            QString("1"),
            const QString &userAgent = QString("Ayvu Messenger/1.0"));

signals:
    void newDeviceReceived(const QString &);
    void byebyeReceived(const QString &);
    void msearchReceived(const QString &);
    void setupEvent(const QString &);

};

} /* namespace ayvu */

#endif /* SSDP_H_ */
