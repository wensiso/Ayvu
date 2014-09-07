/*
 * AppInfo.cpp
 *
 *  Created on: 06/09/2014
 *      Author: wendell
 */

#include <appinfo.h>

namespace ayvu
{

AppInfo *AppInfo::instance = 0;

AppInfo::AppInfo()
{
    m_username = DEFAULT_USERNAME;
}

const QString& AppInfo::getUsername() const
{
    return m_username;
}

void AppInfo::setUsername(const QString& username)
{
    m_username = username;
}


} /* namespace ayvu */
