import bb.cascades 1.0
import bb.system 1.0
import bb.device 1.0

import ayvu.audio 1.0

NavigationPane {
    
    id: navigationPane
    
    property int state: _state.state
    
    property bool stopped: _state.stopped
    property bool inviting: _state.inviting
    property bool incomming: _state.incomming
    property bool talking: _state.talking
    property bool rejected: _state.rejected
    property bool accepted: _state.accepted
    
    property string messageToast
    
    property string callerName: _sessionServer.clientName
    property string callerAddress: _sessionServer.clientAddress
    
    function printAllStates() {
        console.debug("---------- \nActive state: " + _state.getStr(state))
        console.debug("stopped: " + stopped)
        console.debug("inviting: " + inviting)
        console.debug("incomming: " + incomming)
        console.debug("talking: " + talking) 
        console.debug("rejected: " + rejected)
        console.debug("acepted: " + accepted) 
    }
    
    onStateChanged: {
        printAllStates()
        
        if(rejected) {
            _audioControl.toggleAudioOff()
            messageToast = "Call rejected"
            systemToast.show()
        } else if(accepted){
            _audioSender.setAddress(_sessionClient.getStrServerAddress())
            _audioControl.toggleAudioOn()
            messageToast = "Call accepted"
            systemToast.show()
        } else if(incomming) {
            ledController.flash()
            vibrationController.start(50, 500)
            incommingCallDialog.show()            
        }
    }

    onPopTransitionEnded: page.destroy()
    
    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                settingsSheet.createObject().open();
            }
        }
        helpAction: HelpActionItem {
            onTriggered: {
                helpSheet.createObject().open();
            }
        }
        actions: [
            ActionItem {
                title: "About"
                imageSource: "asset:///images/ic_info.png"
                onTriggered: {
                    aboutSheet.createObject().open()
                }
            },
            ActionItem {
                imageSource: "asset:///images/ic_share.png"
                title: "Share"
                onTriggered: {
                    invocation.trigger("bb.action.SHARE")
                }
            }
        ]
    }

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
                    id: listView
                    
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
                        navigationPane.push(contactViewer.createObject(navigationPane))
                    }
                }
                //! [1]
            }
        }

        
    }
    
    attachedObjects: [
        
        ComponentDefinition {
            id: contactViewer
            source: "ContactViewer.qml"
        },
                
        Invocation {
            id: invocation
            query {
                mimeType: "text/plain"
                data: "Use BRisa Binary Light App for BlackBerry 10! Check BRisa Binary Light in the BlackBerry World! Find in http://appworld.blackberry.com/webstore/content/37260887"
            }
        },
        ComponentDefinition {
            id: aboutSheet
            About {
            }
        },
        ComponentDefinition {
            id: settingsSheet
            Settings {
            }
        },
        ComponentDefinition {
            id: helpSheet
            Help {
            }
        },
        SystemToast {
            id: systemToast
            body: messageToast
        },
        VibrationController {
            id: vibrationController
        },
        Led {
            id: ledController
            color: LedColor.Blue
        },
        AudioControl {
            id: _audioControl
        },
        SystemDialog {
            id: incommingCallDialog
            title: "Incomming call from:"
            body: callerName
            
            confirmButton.label: "Accept"
            confirmButton.enabled: true
            cancelButton.label: "Reject"
            cancelButton.enabled: true
            onFinished: {
                vibrationController.stop()
                ledController.cancel()           
                if(incommingCallDialog.result == SystemUiResult.ConfirmButtonSelection) {
                    messageToast = "Initing call..."
                    systemToast.show()
                    _sessionServer.acceptCall()
                    console.debug("[WENDELL]: Accepting call from " + callerName)
                    _sessionClient.setServerAddress(callerAddress)
                    _audioSender.setAddress(callerAddress)
                    _audioControl.toggleAudioOn()
                    
                    _addressBook.setCurrentContact(callerName, callerAddress)
                    _addressBook.viewContact();
                    navigationPane.push(contactViewer.createObject(navigationPane))
                    
                } else {
                    console.debug("[WENDELL]: Rejecting call from " + callerName)
                    _sessionServer.rejectCall()
                }
            }
        }
    ]
    //! [3]
}
