import bb.cascades 1.0

Sheet {
    id: settingsSheet
    
    property bool flag: false
    property bool settingsChanged: false
    
    property string username
    
    onCreationCompleted: {
        username = _app.getUsername()
        console.debug("Old username: "+ username)
        flag = true;
    }
    
    Page {
        titleBar: TitleBar {
            title: "Settings"
            acceptAction: ActionItem {
                title: "Ok"
                onTriggered: {
                    if (settingsChanged) {
                        console.debug("New username: "+ username)
                        _app.setUsername(username)
                        _app.updateSettings();
                    }
                    settingsSheet.close();
                }
            }
            dismissAction: ActionItem {
                title: "Cancel"
                onTriggered: {
                    settingsSheet.close();
                }
            }
        }
        
        ScrollView {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            Container {
                Header {
                    title: "App"
                }
                Container {
                    leftPadding: 20
                    rightPadding: 20
                    bottomPadding: 20
                    Label {
                        multiline: true
                        textStyle.fontSize: FontSize.Large
                        text: "Actually, your username is \"" + username +"\".\n\nChoose your new username:"
                    }
                }
                Container {    
                    horizontalAlignment: HorizontalAlignment.Center
                    bottomPadding: 20
                    layout: StackLayout { 
                        orientation: LayoutOrientation.LeftToRight
                    }
                    
                    TextField {
                        id: userTextField
                        maxWidth: 400
                        hintText: "New username"
                        inputMode: TextFieldInputMode.EmailAddress
                        onTextChanged: {
                            settingsChanged = true
                            username = text
                        }
                    }   
                }
            
                Container {
                    Divider {
                    }
                }
                Header {
                    title: "System"
                }
                StandardListItem {
                    property bool touchIsDown: false
                    title: "Display"
                    description: "For settings of brightness screen"
                    imageSource: "asset:///images/ic_brightness_screen.png"
                    onTouch: {
                        if (event.touchType == TouchType.Up && touchIsDown) {
                            _app.callSettingsCard("settings://display");
                            touchIsDown = false
                        } else if (event.touchType == TouchType.Down) {
                            touchIsDown = true
                        }
                    }
                }
                StandardListItem {
                    property bool touchIsDown: false
                    title: "Network Connections"
                    description: "For settings of network connection"
                    imageSource: "asset:///images/ic_network_connections.png"
                    onTouch: {
                        if (event.touchType == TouchType.Up && touchIsDown) {
                            _app.callSettingsCard("settings://networkconnections");
                            touchIsDown = false
                        } else if (event.touchType == TouchType.Down) {
                            touchIsDown = true
                        }
                    }
                }
            }
        }
    }
}