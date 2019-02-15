import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 1024
    title: qsTr("Stack")



    FontLoader { id: openSansRegular; source: "qrc:/fonts/OpenSans-Regular.ttf" }
    FontLoader { id: openSansBold; source: "qrc:/fonts/OpenSans-Bold.ttf" }
    FontLoader { id: robotoSlabRegular; source: "qrc:/fonts/robotoslab-regular.ttf" }

    MainPage {
        anchors.fill: parent
    }
}
