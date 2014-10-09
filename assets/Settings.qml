import bb.cascades 1.0

Sheet {
    id: settingsSheet
    
    property bool flag: false
    property bool settingsChanged: false
    
    onCreationCompleted: {
        //Fill fields with the actual settings
        flag = true;
    }
    
    Page {
        titleBar: TitleBar {
            title: "Settings"
            acceptAction: ActionItem {
                title: "Ok"
                onTriggered: {
                    if (settingsChanged) {
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
                    Label {
                        multiline: true
                        textStyle.fontSize: FontSize.Large
                        text: "Choose your username: "
                    }
                }
                Container {
                    
                    horizontalAlignment: HorizontalAlignment.Center
                    layout: StackLayout { 
                        orientation: LayoutOrientation.LeftToRight
                    }
                    
                    TextField {
                        id: userTextField
                        maxWidth: 400
                        hintText: "username"
                        inputMode: TextFieldInputMode.Text
                    }   
                }
                Container {
                    Divider {
                    }
                }
                Container {
                    leftPadding: 20
                    rightPadding: 20
                    Label {
                        multiline: true
                        textStyle.fontSize: FontSize.Large
                        text: "Define the name of your device: "
                    }
                }
                Container {
                    
                    horizontalAlignment: HorizontalAlignment.Center
                    layout: StackLayout { 
                        orientation: LayoutOrientation.LeftToRight
                    }
                    
                    TextField {
                        id: addressField
                        maxWidth: 400
                        hintText: "Name of device"
                        inputMode: TextFieldInputMode.Text
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
//                    imageSource: "asset:///images/ic_brightness_screen.png"
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
//                    imageSource: "asset:///images/ic_network_connections.png"
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