/*
 * AppInfo.cpp
 *
 *  Created on: 06/09/2014
 *      Author: wendell
 */

#include <appinfo.h>

using namespace bb::device;

namespace ayvu
{

AppInfo *AppInfo::instance = 0;

AppInfo::AppInfo()
{
    m_username = DEFAULT_USERNAME;
//    m_devicename = m_deviceinfo.deviceName();
//    qDebug() << "DEVICE NAME: " << m_devicename;
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
