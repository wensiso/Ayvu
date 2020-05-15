/*
 * contactservice.h
 *
 *  Created on: 20/10/2014
 *      Author: wendell
 */

#ifndef CONTACTSERVICE_H_
#define CONTACTSERVICE_H_

#include <QObject>

#include <ssdp.h>
#include "contact.h"

namespace ayvu
{

class ContactService : public QObject
{
    Q_OBJECT
public:
    ContactService(QObject *parent = 0);

    const Contact& contactDetails(int id);
    QList<Contact> getContactList();

Q_SIGNALS:
    void contactAdded(int);
    void contactChanged(int);
    void contactDeleted(int);

private slots:
    void onNewDevice(QString);

private:

    SSDP *discoveryService;

    QList<Contact> m_contactList;
    int last_id;

};

} /* namespace ayvu */

#endif /* CONTACTSERVICE_H_ */
