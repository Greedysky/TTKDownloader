#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T11:05:02
#
# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2016 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui network

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

#check Qt version
QT_VER_STRING = $$[QT_VERSION];
QT_VER_STRING = $$split(QT_VER_STRING, ".")
QT_VER_MAJOR = $$member(QT_VER_STRING, 0)
QT_VER_MINOR = $$member(QT_VER_STRING, 1)
QT_VER_PATCH = $$member(QT_VER_STRING, 2)

win32{
    msvc{
        !contains(QMAKE_TARGET.arch, x86_64){
             #support on windows XP
             QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
             QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01
        }
    }

    gcc{
        QMAKE_CXXFLAGS += -std=c++11
        QMAKE_CXXFLAGS += -Wunused-function
        QMAKE_CXXFLAGS += -Wswitch
    }
}

unix:!mac{
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -Wunused-function
    QMAKE_CXXFLAGS += -Wswitch
}

TTKDownloader = 1.0.0.0

DEFINES += DOWNLOADER_LIBRARY

