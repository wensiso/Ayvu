import bb.cascades 1.0
import app.info 1.0

Sheet {
    id: self
    
    attachedObjects: ApplicationInfo {
        id: appInfo
    }
    
    Page {
        
        titleBar: TitleBar {
            dismissAction: ActionItem {
                title: qsTr("Close")
                onTriggered: {
                    self.close()
                }
            }
        }
        Container {
            ScrollView {
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                
                Container {
                    topPadding: 20
                    verticalAlignment: VerticalAlignment.Fill
                    horizontalAlignment: HorizontalAlignment.Fill
                    
//                    ImageView {
//                        imageSource: "asset:///images/onlight.png"
//                        preferredWidth: 150
//                        preferredHeight: 180
//                        scalingMethod: ScalingMethod.AspectFit
//                        horizontalAlignment: HorizontalAlignment.Center
//                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Center
                        
                        Label {
                            text: "Ayvu Wi-Fi Messenger - Version: " + appInfo.version()
                            textStyle.fontWeight: FontWeight.Bold
                        }
                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Center
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        
//                        ImageView {
//                            horizontalAlignment: HorizontalAlignment.Center
//                            imageSource: "asset:///images/compe.png"
//                            scalingMethod: ScalingMethod.AspectFit
//                            preferredHeight: 120
//                            preferredWidth: 275
//                            onTouch: {
//                            }
//                        }
//                        Label {
//                        }
//                        ImageView {
//                            horizontalAlignment: HorizontalAlignment.Center
//                            imageSource: "asset:///images/techcenter.png"
//                            scalingMethod: ScalingMethod.AspectFit
//                            preferredHeight: 120
//                            preferredWidth: 350
//                            onTouch: {
//                            }
//                        }
                    }
                    LabelLink {
                        text: "http://www.compelab.org/"
                        uri: "http://www.compelab.org/"
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    Divider {
                    }
                    Container {
                        leftPadding: 75.0
                        // horizontalAlignment: HorizontalAlignment.Center
                        Label {
                            text: qsTr("Developers")
                            textStyle.fontSize: FontSize.Large
                            textStyle.fontWeight: FontWeight.Bold
                        }
                        Container {
                            Label {
                                text: "Wendell Soares"
                            }
                        }
//                        Container {
//                            Label {
//                                text: "Wendell Soares"
//                            }
//                        }
//                        Label {
//                        }
                    }

                    Divider {
                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Center
                        Button {
                            text: "More Apps"
                            imageSource: "asset:///images/ic_open.png"
                            horizontalAlignment: HorizontalAlignment.Fill
                            
                            onClicked: {
                                _app.callAppWorldVendorCard()
                            }
                        }
                        Button {
                            text: "Post a Review"
                            imageSource: "asset:///images/ic_review.png"
                            horizontalAlignment: HorizontalAlignment.Fill
                            
                            onClicked: {
                                _app.postAReview()
                            }
                        }
                    }
                    Label {
                        text: "Copyright (c) 2014 Wendell Soares"
                        textStyle.fontSize: FontSize.Small
                        verticalAlignment: VerticalAlignment.Bottom
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                }
            }
        }
    }

}