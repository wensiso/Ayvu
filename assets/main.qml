/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.0
import bb.system 1.0
import bb.device 1.0

import ayvu.audio 1.0

Page {
    
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
        
    id: mainScreen
    
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
    
    actions: [
            ActionItem {
            id: startCallAction
            title: "Call"
            imageSource: "asset:///images/ic_microphone.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            enabled: stopped
            onTriggered: {
                if(addressField.text.length==0) {
                    systemToast.body = "Enter an IP address"
                    systemToast.show()
                } else {
                    _state.setInviting()
                    _sessionClient.setServerAddress(addressField.text)
                    _sessionClient.sendInviteMessage();
                }
            }
        },
        
        ActionItem {
            id: stopCallAction
            title: "Stop"
            imageSource: "asset:///images/ic_microphone_mute.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            enabled: !stopped
            onTriggered: {
                _audioControl.toggleAudioOff();
                _state.setStopped();
                _sessionClient.sendFinishMessage()
            }
        }
    ]
    
    Container {
        layout: DockLayout {}
        background: Color.LightGray
        
        Label {
            id: labelIP
            text: _network.getValidIPStr()
            textStyle.color: Color.Black
            
            verticalAlignment: VerticalAlignment.Top
            horizontalAlignment: HorizontalAlignment.Left
        }
        
        Container {
            
            leftPadding: 5
            rightPadding: 5
            bottomPadding: 10
            
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            
            layout: StackLayout { 
                orientation: LayoutOrientation.TopToBottom
            }
            
            Label {
                id: labelAddress
                text: "Enter address: "
                textStyle.color: Color.BlackQML
                
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
            }
            
            Container {
                
                horizontalAlignment: HorizontalAlignment.Center
                
                layout: StackLayout { 
                    orientation: LayoutOrientation.LeftToRight
                }
                
                TextField {
                    id: addressField
                    maxWidth: 400
                    hintText: "IP address"
                    inputMode: TextFieldInputMode.NumbersAndPunctuation
                    enabled: startCallAction.enabled
                }   
            }
            
            Divider {
                opacity: 0
            }
            
            Container {
                
                horizontalAlignment: HorizontalAlignment.Center
                
                layout: StackLayout { 
                    orientation: LayoutOrientation.LeftToRight
                }
                
                Button {
                    text: "Myself"
                    
                    maxWidth: 300
                    enabled: startCallAction.enabled
                    onClicked: {
                        addressField.text = _network.getValidIPStr()
                        addressField.focused
                    }
                }
            }

            Container {
                topPadding: 10
                bottomPadding: 10
                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Center
            
                Label {
                    text: _state.getStr(state)
                    textStyle.color: Color.Black
                }
            
            }
        }
    }
    
    attachedObjects: [
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
                } else {
                    console.debug("[WENDELL]: Rejecting call from " + callerName)
                    _sessionServer.rejectCall()
                }
            }
        }
    ]
}
