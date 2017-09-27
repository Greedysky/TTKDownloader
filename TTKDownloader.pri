# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui network xml

equals(QT_MAJOR_VERSION, 4){
QT       += script
CONFIG   += gcc
}
equals(QT_MAJOR_VERSION, 5){
QT       += widgets
}

UI_DIR = ./.build/ui/
MOC_DIR = ./.build/moc/
OBJECTS_DIR = ./.build/obj
RCC_DIR = ./.build/rcc

##openssl lib check
SSL_DEPANDS = $$OUT_PWD/bin/$$TTKDownloader
win32:{
    SSL_DEPANDS = $$SSL_DEPANDS/ssleay32.dll
    SSL_DEPANDS = $$replace(SSL_DEPANDS, /, \\)
    exists($$SSL_DEPANDS):LIBS += -L../bin/$$TTKDownloader -lssl
}
unix:!mac{
    SSL_DEPANDS = $$SSL_DEPANDS/libssleay32.so
    exists($$SSL_DEPANDS):LIBS += -L../lib/$$TTKDownloader -lssl
}

##check Qt version
QT_VER_STRING = $$[QT_VERSION];
QT_VER_STRING = $$split(QT_VER_STRING, ".")
QT_VER_MAJOR = $$member(QT_VER_STRING, 0)
QT_VER_MINOR = $$member(QT_VER_STRING, 1)
QT_VER_PATCH = $$member(QT_VER_STRING, 2)

include(TTKVersion.pri)

win32{
    LIBS += -lIphlpapi
    equals(QT_MAJOR_VERSION, 5){
        greaterThan(QT_VER_MINOR, 1):QT  += winextras
        msvc{
            LIBS += -L../bin/$$TTKDownloader -lTTKUi -lTTKExtras -lzlib -lTTKZip
            CONFIG +=c++11
            !contains(QMAKE_TARGET.arch, x86_64){
                 #support on windows XP
                 QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
                 QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01
            }
        }

        gcc{
            LIBS += -L../bin/$$TTKDownloader -lTTKUi -lTTKExtras -lzlib -lTTKZip
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }

    equals(QT_MAJOR_VERSION, 4){
        QT  += multimedia
        gcc{
            LIBS += -L../bin/$$TTKDownloader -lTTKUi -lTTKExtras -lzlib -lTTKZip
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }
}

unix:!mac{
    LIBS += -L../lib/$$TTKDownloader -lTTKUi -lTTKExtras -lzlib -lTTKZip
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -Wunused-function
    QMAKE_CXXFLAGS += -Wswitch
}

DEFINES += DOWNLOAD_LIBRARY

#########################################
HEADERS += $$PWD/downloadglobal.h
INCLUDEPATH += $$PWD
#########################################
include(TTKThirdParty/TTKThirdParty.pri)
#########################################
include(TTKModule/TTKModule.pri)

