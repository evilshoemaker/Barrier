QT += quick sql
CONFIG += c++11
CONFIG += qtquickcompiler

QTQUICK_COMPILER_SKIPPED_RESOURCES += www.qrc

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp

RESOURCES += resources.qrc \
    www.qrc

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(database/database.pri)
include(core/core.pri)
include(webface/webface.pri)
include(gpio/gpio.pri)
