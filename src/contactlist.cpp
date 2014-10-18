#include "contactlist.h"
#include "contactviewer.h"

using namespace bb::cascades;

namespace ayvu {

//! [0]
ContactList::ContactList(SSDP *ssdp, QObject *parent)
    : QObject(parent)
    , m_model(new GroupDataModel(this))
    , m_contactViewer(new ContactViewer(ssdp, this))
    , m_currentContactId(-1)
{
    qDebug() << "Contact List created!";

    discoveryService = ssdp;

    // Disable grouping in data model
    m_model->setGrouping(ItemGrouping::None);

    // Ensure to invoke the filterContacts() method whenever a contact has been added, changed or removed
    bool ok = connect(discoveryService, SIGNAL(contactAdded(int)), this, SLOT(filterContacts()));
    Q_ASSERT(ok);
    ok = connect(discoveryService, SIGNAL(contactChanged(int)), this, SLOT(filterContacts()));
    Q_ASSERT(ok);
    ok = connect(discoveryService, SIGNAL(contactDeleted(int)), this, SLOT(filterContacts()));
    Q_ASSERT(ok);

    // Fill the data model with contacts initially
    this->filterContacts();

}
//! [0]

//! [1]
void ContactList::setCurrentContact(const QVariantList &indexPath)
{
    // Extract the ID of the selected contact from the model
    if (indexPath.isEmpty()) {
        m_currentContactId = -1;
    } else {
        const QVariantMap entry = m_model->data(indexPath).toMap();
        m_currentContactId = entry.value("contactId").toInt();
    }
}
//! [1]

//! [4]
void ContactList::viewContact()
{
    // Prepare the contact viewer for displaying the current contact
    m_contactViewer->setContactId(m_currentContactId);
}
//! [4]

bb::cascades::GroupDataModel* ContactList::model() const
{
    return m_model;
}

ContactViewer* ContactList::contactViewer() const
{
    return m_contactViewer;
}


//! [7]
void ContactList::filterContacts()
{
    QList<Contact> *contacts;
    contacts = discoveryService->getContacts();

    // Clear the old contact information from the model
    m_model->clear();

    // Iterate over the list of contact IDs
    foreach (const Contact &idContact, *contacts) {
        // Fetch the complete details for this contact ID
        const Contact contact = discoveryService->contactDetails(idContact.id());

        // Copy the data into a model entry
        QVariantMap entry;
        entry["contactId"] = contact.id();
        entry["firstName"] = contact.getFirstName();
        entry["hostname"] = contact.getHostname();
        entry["ip"] = contact.getIp();

        // Add the entry to the model
        m_model->insert(entry);
    }
}

}
//! [7]
