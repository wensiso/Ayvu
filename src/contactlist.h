#ifndef ADDRESSBOOK_HPP
#define ADDRESSBOOK_HPP

#include <QObject>

#include <bb/cascades/GroupDataModel>

#include "contact.h"
#include "contactservice.h"

namespace ayvu {

class ContactViewer;

/**
 * @short The controller class that makes access to contacts available to the UI.
 */
//! [0]
class ContactList : public QObject
{
    Q_OBJECT

    // The model that provides the filtered list of contacts
    Q_PROPERTY(bb::cascades::GroupDataModel *model READ model CONSTANT);

    // The viewer object for the current contact
    Q_PROPERTY(ayvu::ContactViewer* contactViewer READ contactViewer CONSTANT);


public:
    ContactList(QObject *parent = 0);

public Q_SLOTS:
    /**
     * Marks the contact with the given @p indexPath as current.
     */
    void setCurrentContact(const QVariantList &indexPath);

    void setCurrentContact(const QString name, const QString ip);

    /**
     * Prepares the contact viewer to display the current contact.
     */
    void viewContact();

private Q_SLOTS:
    // Filters the contacts in the model according to the filter property
    void filterContacts();

private:
    // The accessor methods of the properties
    bb::cascades::GroupDataModel* model() const;
    ContactViewer* contactViewer() const;

    ContactService *m_contactService;

    // The property values
    bb::cascades::GroupDataModel* m_model;

    // The controller object for viewing a contact
    ContactViewer* m_contactViewer;

    // The ID of the current contact
    int m_currentContactId;

};
//! [0]
}

#endif
