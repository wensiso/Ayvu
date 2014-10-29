/*
 * contactservice.cpp
 *
 *  Created on: 20/10/2014
 *      Author: wendell
 */

#include <contacts/contactservice.h>

namespace ayvu
{

ContactService::ContactService(QObject *parent) :
        QObject(parent)
{
    Network *net = Network::getInstance();
    discoveryService = net->getSSDP();

    Q_ASSERT_X(discoveryService, "ContactService::ContactService(QObject *parent)" , "discoveryService is null");

    bool ok = connect(discoveryService, SIGNAL(deviceFound(QString)), this, SLOT(onNewDevice(QString)));
    Q_ASSERT(ok);

    m_contactList = QList<Contact>();
    last_id = -1;
}

const Contact& ContactService::contactDetails(int id)
{
    return m_contactList.at(id);
}

QList<Contact> ContactService::getContactList()
{
    return m_contactList;
}

void ContactService::onNewDevice(QString message)
{
    qDebug() << "[ContactService]: new Contact";

    QMap<QString, QString> contactMap = discoveryService->getMapFromMessage(message);
    qDebug() << "MAP: " << contactMap;

    QString user = contactMap["usn"].split("@").at(0);
    QString host = contactMap["usn"].split("@").at(1);
    QString ip = contactMap["location"];

    //If i found myself...
    if(ip.compare(Network::getValidIPStr())==0)
        return;

    Contact c(++last_id);
    c.setFirstName(user);
    c.setHostname(host);
    c.setIp(ip);

    if(!m_contactList.contains(c)) {
        m_contactList.append(c);
        emit contactAdded(last_id);
    } else {
        --last_id;
    }

}

} /* namespace ayvu */

