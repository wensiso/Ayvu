/*
 * AppInfo.cpp
 *
 *  Created on: 06/09/2014
 *      Author: wendell
 */

#include <appinfo.h>
#include <ssdp.h>

using namespace bb::device;

namespace ayvu
{

AppInfo *AppInfo::instance = 0;

AppInfo::AppInfo(QObject *parent) : QObject(parent)
{
    m_username = DEFAULT_USERNAME;
    devices = new QList<QString>();

    ssdp = new SSDP(30);
    ssdp->start();

    Q_ASSERT(connect(ssdp, SIGNAL(newDeviceReceived(QString)), this, SLOT(addNewDevice(QString))));
    Q_ASSERT(connect(ssdp, SIGNAL(byebyeReceived(QString)), this, SLOT(removeDevice(QString))));
}

void AppInfo::addNewDevice(QString device)
{
    devices->append(device);
}

void AppInfo::removeDevice(QString device)
{
    devices->removeOne(device);
}

const QString AppInfo::getUsername() const
{
//    return QString(m_username + "@" + m_devicename);
    return m_username;
}

void AppInfo::setUsername(const QString& username)
{
    m_username = username;
}


} /* namespace ayvu */
