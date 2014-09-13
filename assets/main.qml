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

import bb.cascades 1.2
import bb.system 1.2

Page {
    
    property int state: _state.state
    
    property bool stopped: _state.stopped
    property bool inviting: _state.inviting
    property bool incomming: _state.incomming
    property bool talking: _state.talking
    property bool rejected: _state.rejected
    property bool accepted: _state.accepted
    
    property string messageToast
    property string caller: "tester@testapp"
        
    function printAllStates() {
        console.debug("---------- \nActive state: " + _state.getStr(state))
        console.debug("stopped: " + stopped)
        console.debug("inviting: " + inviting)
        console.debug("incomming: " + incomming)
        console.debug("talking: " + talking) 
        console.debug("rejected: " + rejected)
        console.debug("accpeted: " + accepted) 
    }
    
    onStateChanged: {
        printAllStates()
        
        if(rejected) {
            messageToast = "Call rejected"
            systemToast.show()
        } else if(accepted){
            messageToast = "Call accepted"
            systemToast.show()
        } else if(incomming) {
            incommingCallDialog.show()
        }
    }
    
    id: mainScreen
    
    Menu.definition: MenuDefinition {
        
        actions: [
            ActionItem {
                title: "About"
                imageSource: "asset:///images/ic_info.png"
                onTriggered: {
                    aboutSheet.createObject().open();
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
                textStyle.color: Color.Black
                
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
        ComponentDefinition {
            id: aboutSheet
            About {
            }
        },
        SystemToast {
            id: systemToast
            body: messageToast
        },
        SystemDialog {
            id: incommingCallDialog
            title: "Incomming call from:"
            body: caller
            
            confirmButton.label: "Accept"
            confirmButton.enabled: true
            cancelButton.label: "Reject"
            cancelButton.enabled: true
            onFinished: {
                if(incommingCallDialog.result == SystemUiResult.ConfirmButtonSelection) {
                    messageToast = "Initing call..."
                    systemToast.show()
                    _sessionServer.acceptCall()
                    console.debug("[WENDELL]: QML Incomming call from " + caller)
//                    _sessionManager.setAddress(incommingCallFrom)
//                    _audioSender.setAddress(incommingCallFrom)
//                    _audioControl.toggleAudioOn()
                } else {
                    _sessionServer.rejectCall()
                }
            }
        }
    ]
}
