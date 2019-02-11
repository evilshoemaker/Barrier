import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import app 1.0

import "controls"

Item {
    id: page

    state: "inputState"

    signal inputCarNumberEnded()

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 34
        anchors.bottomMargin: 34

        ColumnLayout {
            spacing: 0
            NumberControl {
                id: carNumber

                Layout.preferredWidth: 400
                Layout.preferredHeight: 90
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                id: inputHelpText
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

            Text {
                id: notFoundText
                Layout.topMargin: 24
                Layout.fillWidth: true
                Layout.leftMargin: 45
                Layout.rightMargin: 45

                horizontalAlignment: Qt.AlignHCenter

                font.pixelSize: 36
                font.family: openSansRegular.name
                font.capitalization: Font.AllUppercase

                opacity: 0.8

                visible: false

                wrapMode: Text.WordWrap

                color: "red"

                text: "Автомобиль с указанным номером не найден"
            }
        }

        ListView {
            id: carNumberListView
            model: carNumberModel
            spacing: 10

            Layout.topMargin: 24
            Layout.leftMargin: 45
            Layout.rightMargin: 45

            delegate: CarNumber {
                x: (carNumberListView.width / 2) - (width / 2)
                number: carNumber
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }


    KeyEventHandler {
        enabled: page.state == 'inputState'

        onNextDigit: { 
            carNumber.number += digit

            if (carNumber.number.length == 3)
            {
                search()
            }
        }

        onDeleteDigit: {
            carNumber.number = carNumber.number.substring(0, carNumber.number.length - 1)
        }
    }

    function search()
    {
        page.state = "searchState"
        carNumberModel.search(carNumber.number)
    }

    CarNumberInfoModel {
        id: carNumberModel

        onSearchCompleted: {
            if (isSearch) {
                page.state = "foundState"
            }
            else {
                page.state = "notFoundState"
                resetTimer.start()
            }
        }
    }

    Timer {
        id: resetTimer
        repeat: false
        interval: 3000

        onTriggered: {
            page.state = "inputState"
        }
    }

    states: [
        State {
            name: "searchState"

            PropertyChanges {
                target: carNumberListView
                visible: false
            }

            PropertyChanges {
                target: notFoundText
                visible: false
            }

            PropertyChanges {
                target: inputHelpText
                visible: true
            }
        },

        State {
            name: "foundState"
            PropertyChanges {
                target: carNumberListView
                visible: true
            }

            PropertyChanges {
                target: notFoundText
                visible: false
            }

            PropertyChanges {
                target: inputHelpText
                visible: false
            }
        },

        State {
            name: "notFoundState"
            PropertyChanges {
                target: carNumberListView
                visible: false
            }

            PropertyChanges {
                target: notFoundText
                visible: true
            }

            PropertyChanges {
                target: inputHelpText
                visible: false
            }
        },

        State {
            name: "inputState"
            PropertyChanges {
                target: carNumberListView
                visible: false
            }

            PropertyChanges {
                target: notFoundText
                visible: false
            }

            PropertyChanges {
                target: inputHelpText
                visible: true
            }

            StateChangeScript {
                script: {
                    carNumber.number = ""
                }
            }
        }
    ]
}

