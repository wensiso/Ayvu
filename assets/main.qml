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

Page {
    
    id: mainScreen
    
    property bool stopped: true
    property bool calling: false
    property bool incommingcall: false
    property bool talking: false
    
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
        },
        
        ActionItem {
            id: stopCallAction
            title: "Stop"
            imageSource: "asset:///images/ic_microphone_mute.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            enabled: calling || incommingcall || talking
        }
    ]
    
    Container {
        layout: DockLayout {}
        background: Color.LightGray
        
        Label {
            id: labelIP
//            text: _audioSender.getValidIPStr()
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
                        addressField.text = network.getValidIPStr()
                        addressField.focused
                    }
                }
            }
        }
    }
    
    attachedObjects: [
        ComponentDefinition {
            id: aboutSheet
            About {
            }
        }
    ]
}
