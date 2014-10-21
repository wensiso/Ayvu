import bb.cascades 1.0

Page {
    id: root

    titleBar: TitleBar {
        title: qsTr ("Contact Details")
    }

    Container {
        layout: DockLayout {}

        // The background image
        BackgroundImage {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
        }

        AddressbookScrollView {
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Top

                //! [0]
                ViewerField {
                    horizontalAlignment: HorizontalAlignment.Fill
                    title: qsTr("first name")
                    value: _addressBook.contactViewer.firstName
                }

                ViewerField {
                    horizontalAlignment: HorizontalAlignment.Fill
                    topMargin: ui.du(5.5)

                    title: qsTr("hostname")
                    value: _addressBook.contactViewer.hostname
                }
                //! [0]

                ViewerField {
                    horizontalAlignment: HorizontalAlignment.Fill
                    topMargin: ui.du(5.5)

                    title: qsTr("ip")
                    value: _addressBook.contactViewer.ip
                }
            }
        }
    }
    
    //! [1]
    actions: [
        ActionItem {
            title: qsTr ("Call")
            imageSource: "asset:///images/action_editcontact.png"
            
//            onTriggered: {
//                _addressBook.editContact()
//                navigationPane.push(contactEditor.createObject())
//            }
        }
    ]
}
