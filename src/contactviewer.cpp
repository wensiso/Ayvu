#include "contactviewer.h"

namespace ayvu {

//! [0]
ContactViewer::ContactViewer(ContactService *service, QObject *parent)
    : QObject(parent)
    , m_contactService(service)
    , m_contactId(-1)
{
    qDebug() << "ContactViewer: created! ";

    // Ensure to invoke the contactsChanged() method whenever a contact has been changed
    bool ok = connect(m_contactService, SIGNAL(contactChanged(int)), SLOT(contactChanged(int)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}
//! [0]

//! [1]
void ContactViewer::updateContact()
{
    // Store previous values
    const QString oldFirstName = m_firstName;
    const QString oldHostname = m_hostname;
    const QString oldIp = m_ip;

    // Fetch new values from persistent storage
    const Contact contact = m_contactService->contactDetails(m_contactId);

    m_firstName = contact.getFirstName();
    m_hostname = contact.getHostname();
    m_ip = contact.getIp();

    // Check whether values have changed
    if (oldFirstName != m_firstName)
        emit firstNameChanged();

    if (oldHostname != m_hostname)
        emit hostnameChanged();

    if (oldIp != m_ip)
        emit ipChanged();
}
//! [1]

//! [2]
void ContactViewer::contactChanged(const int &contactId)
{
    /**
     * Call updateContact() only if the contact we are currently displaying
     * has been changed.
     */
    if (contactId == m_contactId)
        updateContact();
}
//! [2]

//! [3]
void ContactViewer::setContactId(int contactId)
{
    if (m_contactId == contactId)
        return;

    m_contactId = contactId;

    // Trigger a refetch of the contact for the new ID
    updateContact();
}
//! [3]

QString ContactViewer::firstName() const
{
    return m_firstName;
}

QString ContactViewer::hostname() const
{
    return m_hostname;
}


QString ContactViewer::ip() const
{
    return m_ip;
}



}
