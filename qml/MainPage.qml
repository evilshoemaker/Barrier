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

                //scale: 1.5

                Layout.preferredWidth: 600
                Layout.preferredHeight: 120
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                id: inputHelpText
                Layout.topMargin: 38
                Layout.fillWidth: true
                Layout.leftMargin: 45
                Layout.rightMargin: 45

                horizontalAlignment: Qt.AlignHCenter

                font.pixelSize: 48
                font.family: openSansRegular.name
                font.capitalization: Font.AllUppercase

                opacity: 0.8

                wrapMode: Text.WordWrap

                text: "Введите 3 цифры номера автомобиля"
            }

            Text {
                id: notFoundText
                Layout.topMargin: 24
                Layout.fillWidth: true
                Layout.leftMargin: 45
                Layout.rightMargin: 45

                horizontalAlignment: Qt.AlignHCenter

                font.pixelSize: 48
                font.family: openSansRegular.name
                font.capitalization: Font.AllUppercase

                opacity: 0.8

                visible: false

                wrapMode: Text.WordWrap

                color: "red"

                text: "Автомобиль с указанным номером не найден"
            }
        }

        Item {
            id: carNumberListViewItem

            visible: false

            Layout.topMargin: 24
            Layout.leftMargin: 45
            Layout.rightMargin: 45

            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                Text {
                    Layout.fillWidth: true

                    Layout.topMargin: 24
                    Layout.leftMargin: 45
                    Layout.rightMargin: 45

                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter

                    font.pixelSize: 36
                    font.family: openSansRegular.name
                    //font.capitalization: Font.AllUppercase

                    wrapMode: Text.WordWrap

                    text: "Нажмите на клавиатуре от 1-9 для открытия шлагбаума. Отмена Esc"
                }

                ListView {
                    id: carNumberListView

                    model: carNumberModel
                    spacing: 20

                    delegate: RowLayout {

                        x: (carNumberListView.width / 2) - (width / 2)

                        Rectangle {
                            Layout.fillHeight: true

                            Layout.preferredWidth: 100

                            border.width: 2
                            border.color: "#000"

                            radius: 5

                            //scale: 1.5

                            Text {
                                anchors.centerIn: parent

                                horizontalAlignment: Qt.AlignHCenter
                                verticalAlignment: Qt.AlignVCenter

                                font.pixelSize: 48
                                font.family: openSansRegular.name

                                text: (index + 1)
                            }

                        }

                        CarNumber {
                            Layout.leftMargin: 20
                            number: carNumber
                            //scale: 1.5
                        }
                    }

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.topMargin: 10
                }
            }
        }

        Text {
            id: openningBarrierText

            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.topMargin: 24
            Layout.leftMargin: 45
            Layout.rightMargin: 45

            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter

            font.pixelSize: 36
            font.family: openSansRegular.name
            font.capitalization: Font.AllUppercase

            visible: false

            color: "green"

            wrapMode: Text.WordWrap

            text: "Открытие шлагбаума"
        }
    }

    KeyEventHandler {
        //enabled: page.state == 'inputState'

        onNextDigit: {
            if (page.state == 'inputState') {
                carNumber.number += digit

                if (carNumber.number.length == 3)
                {
                    search()
                }
            }
            else if (page.state == 'foundState')
            {
                var index = parseInt(digit, 10) - 1;

                if (carNumberModel.count > index && index > -1)
                {
                    page.state = "openningBarrier";

                    var carNumberInfo  = carNumberModel.at(index);
                    carNumber.fullNumber = carNumberInfo.carNumber;
                    databaseLogger.openBarrier(carNumberInfo)
                    console.log("open " + index + " " + carNumberInfo.carNumber);
                    gpioResetTimer.start();
                }
            }
        }

        onDeleteDigit: {
            if (page.state == 'inputState') {
                carNumber.number = carNumber.number.substring(0, carNumber.number.length - 1)
            }
        }

        onEscaped: {
            if (page.state == 'inputState') {
                carNumber.number = "";
            }
            else {
                page.state = "inputState";
            }
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

    Timer {
        id: gpioResetTimer
        repeat: false
        interval: 1500

        onRunningChanged: {
            if (gpioResetTimer.running)
                gpio.digitalWrite(14, 0);
        }

        onTriggered: {
            gpio.digitalWrite(14, 1);
        }
    }

    Gpio {
        id: gpio

        Component.onCompleted: {
            gpio.init(14);
            gpio.digitalWrite(14, 1);
        }
    }

    states: [
        State {
            name: "searchState"

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
                target: carNumberListViewItem
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
                    carNumber.fullNumber = ""
                }
            }
        },

        State {
            name: "openningBarrier"

            PropertyChanges {
                target: notFoundText
                visible: false
            }

            PropertyChanges {
                target: inputHelpText
                visible: false
            }

            StateChangeScript {
                script: {
                    resetTimer.start();
                }
            }

            PropertyChanges {
                target: openningBarrierText
                visible: true
            }
        }
    ]
}

