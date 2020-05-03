QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH = include/

SOURCES += \
    src/appsettings.cpp \
    src/filtertab.cpp \
    src/filter.cpp \
    src/lowpassfilter.cpp \
    src/filteranalyzer.cpp \
    src/filterdesigner.cpp \
    src/main.cpp \
    src/filterdesignermain.cpp \
    src/windowdesigner.cpp


HEADERS += \
    include/appsettings.h \
    include/filtertab.h \
    include/filter.h \
    include/filteranalyzer.h \
    include/filterdesigner.h \
    include/filterdesignermain.h \
    include/sigproc.h \
    include/lowpassfilter.h \
    include/windowdesigner.h \
    version.h

FORMS += \
    forms/appsettings.ui \
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
