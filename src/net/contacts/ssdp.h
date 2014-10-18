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
#include <QList>
#include <QSettings>

#include <network.h>
#include <contact.h>
#include "ssdpprotocol.h"

namespace ayvu {

class SSDP: public QObject {
Q_OBJECT

public:
    explicit SSDP(int interval = 1, QString usn="", QObject *parent = 0);
    ~SSDP();

    void init();
    bool isInitialized() const;

    void start();
    void stop();
    void doubleDiscover(const QString &type = QString("ayvu:all"),
            const QString &mx = QString("1"), const QString &userAgent =
                    QString("Ayvu Messenger/1.0"));

    const Contact& contactDetails(int id);
    QList<Contact>* getContacts();

signals:
    void contactAdded(int);
    void contactChanged(int);
    void contactDeleted(int);

    void deviceAlive(const QString &);
    void byebyeReceived(const QString &);
    void msearchReceived(const QString &);
    void setupEvent(const QString &);

    void multicastError();

private slots:
    void datagramReceived();

public slots:
    void discover(const QString &type = QString("ayvu:all"), const QString &mx =
            QString("1"),
            const QString &userAgent = QString("Ayvu Messenger/1.0"));

private:

    void parseMessage(const QString &);
    QMap<QString, QString> getMapFromMessage(QString message);
    QString *getValue(QMapIterator<QString, QString> &, QString);

    QTimer *discoverTimer;
    QUdpSocket *udpSocket;
    int interval;
    QString USN;
    bool initialized;

    QList<Contact> *contacts_list;
    int last_id;

};

} /* namespace ayvu */

#endif /* SSDP_H_ */
