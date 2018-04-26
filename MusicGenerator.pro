TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

unix:!macx {
    QMAKE_CXXFLAGS += -std=c++11  -Wno-unused-parameter -Wno-unused-variable
}
win32-g++ {
    QMAKE_CXXFLAGS += -std=c++11  -Wno-unused-parameter -Wno-unused-variable
}

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

SOURCES += src/main.cpp \
    src/serialization/wave.cpp \
    src/core/note.cpp \
    src/core/gamme.cpp \
    src/core/accord.cpp \
    src/core/melody.cpp

HEADERS += \
    include/serialization/wave.h \
    include/core/note.h \
    include/core/gamme.h \
    include/core/accord.h \
    include/core/melody.h
