import QtQuick 2.0

Item {
    id: control

    focus: true

    property bool enabled: true

    signal nextDigit(string digit)
    signal deleteDigit()
    signal escaped()
    signal plusPressed()
    signal minusPressed()


    Keys.onPressed: {
        if (!enabled)
            return;

        if (event.key === Qt.Key_0 ||
                event.key === Qt.Key_1 ||
                event.key === Qt.Key_2 ||
                event.key === Qt.Key_3 ||
                event.key === Qt.Key_4 ||
                event.key === Qt.Key_5 ||
                event.key === Qt.Key_6 ||
                event.key === Qt.Key_7 ||
                event.key === Qt.Key_8 ||
                event.key === Qt.Key_9)
        {
            nextDigit(event.text)
        }

        if (event.key === Qt.Key_Backspace ||
                event.key === Qt.Key_Delete)
        {
            deleteDigit();
        }

        if (event.key === Qt.Key_Escape) {
            escaped();
        }

        if (event.key === Qt.Key_Minus) {
            minusPressed();
        }

        if (event.key === Qt.Key_Plus) {
            plusPressed();
        }
    }
}
