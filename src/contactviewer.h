#ifndef CONTACTVIEWER_HPP
#define CONTACTVIEWER_HPP

#include <QObject>

#include "contact.h"
#include "contactservice.h"

namespace ayvu {

/**
 * @short A controller object to encapsulate the logic of the contact viewer
 *
 * The ContactViewer class is an UI-independent representation of the contact viewer,
 * that provides all the functionality and data as slots and properties.
 * It encapsulates all the logic of loading a contact from the persistent storage,
 * provide its data as properties and update the properties if the contact has
 * changed in the storage backend.
 */
//! [0]
class ContactViewer : public QObject
{
    Q_OBJECT

    // The data properties of the contact that is displayed
    Q_PROPERTY(QString firstName READ firstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString hostname READ hostname NOTIFY hostnameChanged)
    Q_PROPERTY(QString ip READ ip NOTIFY ipChanged)

public:
    ContactViewer(ContactService *service, QObject *parent = 0);

    // Sets the ID of the contact that should be displayed.
    void setContactId(int contactId);

Q_SIGNALS:
    // The change notification signals of the properties
    void firstNameChanged();
    void hostnameChanged();
    void ipChanged();

private Q_SLOTS:
    /**
     * This slot is invoked whenever the contact service reports that a contact has been changed.
     */
    void contactChanged(const int &contactId);

private:
    // The accessor methods of the properties
    QString firstName() const;
    QString hostname() const;
    QString ip() const;

    // Loads the contact from the persistent storage and updates the properties
    void updateContact();

    // The central object to access the contact service
    ContactService* m_contactService;

    // The ID of the contact that is displayed
    int m_contactId;

    // The property values
    QString m_firstName;
    QString m_hostname;
    QString m_ip;
};
//! [0]
}

#endif
