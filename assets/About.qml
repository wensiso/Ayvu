import bb.cascades 1.0

Sheet {
    id: aboutSheet
    Page {

        titleBar: TitleBar {
            dismissAction: ActionItem {
                title: qsTr("Close")
                onTriggered: {
                    aboutSheet.close()
                }
            }
        }
        Container {
            background: Color.White
            ScrollView {
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                Container {
                    verticalAlignment: VerticalAlignment.Fill
                    horizontalAlignment: HorizontalAlignment.Fill
                    Container {
                        horizontalAlignment: HorizontalAlignment.Center
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
//                        ImageView {
//                            horizontalAlignment: HorizontalAlignment.Center
//                            imageSource: "asset:///images/compe.png"
//                            scalingMethod: ScalingMethod.AspectFit
//                            preferredHeight: 200
//                            preferredWidth: 275
//                            onTouch: {
//                            }
//                        }
                        Label {
                        }
//                        ImageView {
//                            horizontalAlignment: HorizontalAlignment.Center
//                            imageSource: "asset:///images/techcenter.png"
//                            scalingMethod: ScalingMethod.AspectFit
//                            preferredHeight: 200
//                            preferredWidth: 325
//                            onTouch: {
//                            }
//                        }
                    }
                    Divider {
                    }
                    Label {
                        text: "Ayvu Messenger - V 1.0.0"
                        textStyle.fontWeight: FontWeight.Bold
                        horizontalAlignment: HorizontalAlignment.Center
                        textStyle.color: Color.Black
                    }
                    Divider {
                    }
                    Container {
                        leftPadding: 75.0
                        // horizontalAlignment: HorizontalAlignment.Center
                        Label {
                            text: qsTr("Developers")
                            textStyle.fontSize: FontSize.XLarge
                            textStyle.fontWeight: FontWeight.Bold
                            textStyle.color: Color.Black
                        }
                        Container {
                            Label {
                                text: "Wendell Soares"
                                textStyle.fontSize: FontSize.Large
                                textStyle.color: Color.Black
                            }
                        }
                        Label {
                        }
                    }
                }
            }
        }
    }

}
