import bb.cascades 1.0

NavigationPane {
    id: navigationPane

    onPopTransitionEnded: page.destroy()

    // The main page
    Page {
        Container {
            layout: DockLayout {}

            // The background image
            BackgroundImage {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
            }

            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                
                //! [1]
                // The list view with all contacts
                ListView {
                    dataModel: _addressBook.model

                    listItemComponents: ListItemComponent {
                        type: "item"

                        StandardListItem {
                            title: qsTr ("%1@%2").arg(ListItemData.firstName).arg(ListItemData.hostname)
                            description: ListItemData.ip
                        }
                    }

                    onTriggered: {
                        clearSelection()
                        select(indexPath)

                        _addressBook.setCurrentContact(indexPath)

                        _addressBook.viewContact();
                        navigationPane.push(contactViewer.createObject())
                    }
                }
                //! [1]
            }
        }

        
    }

    //! [3]
    attachedObjects: [
        ComponentDefinition {
            id: contactViewer
            source: "ContactViewer.qml"
        }
    ]
    //! [3]
}
