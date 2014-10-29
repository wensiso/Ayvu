/*
 * contact.h
 *
 *  Created on: 17/10/2014
 *      Author: wendell
 */

#ifndef CONTACT_H_
#define CONTACT_H_

namespace ayvu
{

class Contact
{
public:
    Contact(int id, QString fname="", QString hostname="", QString ip="");
    Contact(const Contact &c);

    const QString& getFirstName() const;
    void setFirstName(const QString& firstName);
    int id() const;
    const QString& getIp() const;
    void setIp(const QString& ip);
    const QString& getHostname() const;
    void setHostname(const QString& hostname);

    //return true if the messages are equal, false otherwise
    inline bool operator == (const Contact &c) const {
        return (c.m_firstName == m_firstName) && (c.m_hostname == m_hostname) && (c.m_ip == m_ip);
    }


private:
    int m_id;
    QString m_firstName;
    QString m_hostname;
    QString m_ip;

};

} /* namespace ayvu */

#endif /* CONTACT_H_ */
