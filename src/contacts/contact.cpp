/*
 * contact.cpp
 *
 *  Created on: 17/10/2014
 *      Author: wendell
 */

#include <contact.h>

namespace ayvu
{

Contact::Contact(int id, QString fname, QString hostname, QString ip)
{
    m_id = id;
    m_firstName = fname;
    m_hostname = hostname;
    m_ip = ip;

}

Contact::Contact(const Contact &c)
{
    m_id = c.m_id;
    m_firstName = c.m_firstName;
    m_hostname = c.m_hostname;
    m_ip = c.m_ip;

}

const QString& Contact::getFirstName() const
{
    return m_firstName;
}

void Contact::setFirstName(const QString& firstName)
{
    m_firstName = firstName;
}

int Contact::id() const
{
    return m_id;
}

const QString& Contact::getIp() const
{
    return m_ip;
}

void Contact::setIp(const QString& ip)
{
    m_ip = ip;
}

const QString& Contact::getHostname() const
{
    return m_hostname;
}

void Contact::setHostname(const QString& hostname)
{
    m_hostname = hostname;
}

} /* namespace ayvu */
