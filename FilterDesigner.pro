QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = include/

SOURCES += \
    src/filtertab.cpp \
    src/filter.cpp \
    src/lowpassfilter.cpp \
    src/filteranalyzer.cpp \
    src/filterdesigner.cpp \
    src/main.cpp \
    src/filterdesignermain.cpp \ \
    src/windowdesigner.cpp


HEADERS += \
    include/filtertab.h \
    include/filter.h \
    include/filteranalyzer.h \
    include/filterdesigner.h \
    include/filterdesignermain.h \
    include/sigproc.h \
    include/lowpassfilter.h \ \
    include/windowdesigner.h

FORMS += \
    forms/filtertab.ui \
    forms/filteranalyzer.ui \
    forms/filterdesigner.ui \
    forms/filterdesignermain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    python/fft_test.py
