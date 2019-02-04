import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import "controls"

Item {
    id: page

    signal inputCarNumberEnded()

    ColumnLayout {
        anchors.fill: parent

        ColumnLayout {
            NumberControl {
                id: carNumber

                Layout.preferredWidth: 400
                Layout.preferredHeight: 90
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Text {
                Layout.topMargin: 24
                Layout.fillWidth: true
                Layout.leftMargin: 45
                Layout.rightMargin: 45

                horizontalAlignment: Qt.AlignHCenter

                font.pixelSize: 36
                font.family: openSansRegular.name
                font.capitalization: Font.AllUppercase

                opacity: 0.8

                wrapMode: Text.WordWrap

                text: "Введите 3 цифры номера атомобиля"
            }
        }
    }


    KeyEventHandler {
        onNextDigit: {
            carNumber.number += digit
        }

        onDeleteDigit: {
            carNumber.number = carNumber.number.substring(0, carNumber.number.length - 1)
        }
    }
}
