import bb.cascades 1.0

Page {
    id: root
        
    titleBar: TitleBar {
        title: qsTr ("Contact Details")
    }
    
    actions: [
        ActionItem {
            id: startCallAction
            title: "Call"
            imageSource: "asset:///images/ic_phone.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            enabled: navigationPane.stopped && (ip.value.length > 0)
            onTriggered: {
                _state.setInviting()
                _sessionClient.setServerAddress(ip.value)
                _sessionClient.sendInviteMessage();
            }
        },
        
        ActionItem {
            id: stopCallAction
            title: "Stop"
            imageSource: "asset:///images/ic_stop.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            enabled: !navigationPane.stopped
            onTriggered: {
                _audioControl.toggleAudioOff();
                _state.setStopped();
                _sessionClient.sendFinishMessage()
            }
        }
    ]

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
                    id: firstname
                    horizontalAlignment: HorizontalAlignment.Fill
                    title: qsTr("first name")
                    value: _addressBook.contactViewer.firstName
                }

                ViewerField {
                    id: hostname
                    horizontalAlignment: HorizontalAlignment.Fill
                    topMargin: ui.du(5.5)

                    title: qsTr("hostname")
                    value: _addressBook.contactViewer.hostname
                }
                //! [0]

                ViewerField {
                    id: ip
                    horizontalAlignment: HorizontalAlignment.Fill
                    topMargin: ui.du(5.5)

                    title: qsTr("ip")
                    value: _addressBook.contactViewer.ip

                }
            }
        }
    }
}
