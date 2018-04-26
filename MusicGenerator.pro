TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

SOURCES += src/main.cpp \
    src/serialization/wave.cpp \
    src/core/note.cpp \
    src/core/gamme.cpp \
    src/core/accord.cpp

HEADERS += \
    include/serialization/wave.h \
    include/core/note.h \
    include/core/gamme.h \
    include/core/accord.h
