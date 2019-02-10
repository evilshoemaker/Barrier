import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Item {
    id: control

    width: 300
    height: 60

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
                Layout.leftMargin: 24
                Layout.rightMargin: 24

                spacing: 0

                Text {

                    Layout.alignment: Qt.AlignBottom

                    font.pixelSize: 36
                    font.family: openSansRegular.name

                    opacity: 0.5

                    text: "A"
                }

                Text {

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom

                    horizontalAlignment: Text.AlignHCenter

                    font.pixelSize: 42
                    font.family: openSansRegular.name

                    opacity: control.number.length > 0 ? 1 : 0.5

                    text: control.number.length > 0 ? control.number : "000"
                }

                /*Text {
                    Layout.alignment: Qt.AlignBottom

                    font.pixelSize: 36
                    font.family: openSansRegular.name

                    opacity: 0.5

                    text: "A"
                }*/

                Text {
                    Layout.leftMargin: 10
                    Layout.alignment: Qt.AlignBottom

                    font.pixelSize: 36
                    font.family: openSansRegular.name

                    opacity: 0.5

                    text: "A"
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
                        Layout.topMargin: 2

                        font.pixelSize: 26
                        font.family: openSansRegular.name

                        opacity: 0.5

                        text: "000"
                    }

                    RowLayout {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.bottomMargin: 5

                        Text {
                            Layout.alignment: Qt.AlignBottom
                            verticalAlignment: Text.AlignBottom

                            font.pixelSize: 14
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
}
