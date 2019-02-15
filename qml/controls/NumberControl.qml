import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import app 1.0

Item {
    id: control

    property string number: ""
    property string fullNumber: ""

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
                Layout.leftMargin: 36
                Layout.rightMargin: 36

                spacing: 0

                Text {

                    Layout.alignment: Qt.AlignBottom

                    font.pixelSize: 42
                    font.family: openSansRegular.name

                    opacity: carNumberParser.char1.length > 0 ? 1 : 0.5

                    text: carNumberParser.char1.length > 0 ? carNumberParser.char1 : "A"
                }

                Text {

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom

                    horizontalAlignment: Text.AlignHCenter

                    font.pixelSize: 52
                    font.family: openSansRegular.name

                    opacity: control.number.length > 0 ? 1 : 0.5

                    text: control.number.length > 0 ? control.number : "000"
                }

                Text {
                    Layout.leftMargin: 10
                    Layout.alignment: Qt.AlignBottom

                    font.pixelSize: 42
                    font.family: openSansRegular.name

                    opacity: carNumberParser.char2.length > 0 ? 1 : 0.5

                    text: carNumberParser.char2.length > 0 ? carNumberParser.char2 : "AA"
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
                        Layout.topMargin: 5

                        font.pixelSize: 38
                        font.family: openSansRegular.name

                        opacity: carNumberParser.region.length > 0 ? 1 : 0.5

                        text: carNumberParser.region.length > 0 ? carNumberParser.region : "000"
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
                            Layout.preferredHeight: 20
                            Layout.preferredWidth: 30

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
        number: control.fullNumber
    }
}
