QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csvhandler.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    csvhandler.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

SUBDIRS += \
    external


unix{
    include(external/qtcsv/qtcsv.pri)
}

win32{
    #include(external\qtcsv\qtcsv.pri)
    LIBS += "C:/Users/mateu/Documents/GitHub/Simple-UDP-Server/build-SimpleUdpServer-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/qtcsv.dll"
}

include(external/qtcsv/qtcsv.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
