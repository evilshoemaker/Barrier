include(httpserver/httpserver.pri)
include(controller/controller.pri)
include(templateengine/templateengine.pri)

HEADERS += \
    $$PWD/WebFace.h \
    $$PWD/RequestMapper.h

SOURCES += \
    $$PWD/WebFace.cpp \
    $$PWD/RequestMapper.cpp
