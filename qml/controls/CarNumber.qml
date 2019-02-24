import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import app 1.0

Item {
    id: control

    width: 350
    height: 90

    property string number: ""

    Rectangle {
        anchors.fill: parent

        color: "#fff"

        border.width: 3
        border.color: "#000"

        radius: 10

        RowLayout {
            anchors.fill: parent

            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                //Layout.leftMargin: 15
                //Layout.rightMargin: 15

                spacing: 0

                Item {
                    Layout.fillWidth: true
                }

                Text {

                    Layout.alignment: Qt.AlignBottom

                    font.pixelSize: 42
                    font.family: openSansRegular.name

                    text: carNumberParser.char1
                }

                Text {
                    Layout.leftMargin: 10

                    Layout.alignment: Qt.AlignBottom

                    horizontalAlignment: Text.AlignHCenter

                    font.pixelSize: 52
                    font.family: openSansRegular.name

                    //opacity: control.number.length > 0 ? 1 : 0.5

                    text: carNumberParser.digital//control.number.length > 0 ? control.number : "000"
                }

                Text {
                    Layout.leftMargin: 10
                    Layout.alignment: Qt.AlignBottom

                    font.pixelSize: 42
                    font.family: openSansRegular.name

                    text: carNumberParser.char2
                }

                Item {
                    Layout.fillWidth: true
                }

            }

            Item {
                Layout.fillHeight: true
                Layout.preferredWidth: 100

                Rectangle {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    width: 3

                    color: "#000"
                }

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 0

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillHeight: true
                        Layout.topMargin: 10

                        font.pixelSize: 28
                        font.family: openSansRegular.name

                        //opacity: 0.5

                        text: carNumberParser.region
                    }

                    RowLayout {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.bottomMargin: 10

                        Text {
                            Layout.alignment: Qt.AlignBottom
                            verticalAlignment: Text.AlignBottom

                            font.pixelSize: 18
                            font.family: openSansRegular.name

                            text: "RUS"
                        }

                        Image {
                            Layout.preferredHeight: 15
                            Layout.preferredWidth: 20

                            //Layout.alignment: Qt.AlignBottom

                            sourceSize.height: height
                            sourceSize.width: width

                            source: "qrc:/images/flag_of_russia.svg"
                        }
                    }
                }
            }
        }
    }

    CarNumberParser {
        id: carNumberParser
        number: control.number
    }
}
