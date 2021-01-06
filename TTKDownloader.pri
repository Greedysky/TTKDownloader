# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2021 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# =================================================

QT       += core gui network xml

equals(QT_MAJOR_VERSION, 4){
QT       += script
CONFIG   += gcc
}
equals(QT_MAJOR_VERSION, 5){
QT       += widgets
}

include($$PWD/TTKVersion.pri)
DESTDIR = $$OUT_PWD/../bin/$$TTKDownloader

##openssl lib check
win32:{
    SSL_DEPANDS = $$DESTDIR/ssleay32.dll
    SSL_DEPANDS = $$replace(SSL_DEPANDS, /, \\)
    exists($$SSL_DEPANDS):LIBS += -L$$DESTDIR -lssl
}
unix:!mac{
    SSL_DEPANDS = $$OUT_PWD/../lib/$$TTKDownloader/libssleay32.so
    exists($$SSL_DEPANDS):LIBS += -L$$DESTDIR -lssl
}

win32{
    LIBS += -lIphlpapi
    equals(QT_MAJOR_VERSION, 5){
        greaterThan(QT_MINOR_VERSION, 1):QT  += winextras
        msvc{
            LIBS += -lshell32 -luser32
            LIBS += -L$$DESTDIR -lTTKUi -lTTKExtras -lzlib -lTTKZip
            CONFIG +=c++11
            !contains(QMAKE_TARGET.arch, x86_64){
                 #support on windows XP
                 QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
                 QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01
            }
        }

        gcc{
            LIBS += -L$$DESTDIR -lTTKUi -lTTKExtras -lzlib -lTTKZip
            QMAKE_CXXFLAGS += -std=c++11 -Wunused-function -Wswitch
        }
    }

    equals(QT_MAJOR_VERSION, 4){
        QT  += multimedia
        gcc{
            LIBS += -L$$DESTDIR -lTTKUi -lTTKExtras -lzlib -lTTKZip
            QMAKE_CXXFLAGS += -std=c++11 -Wunused-function -Wswitch
        }
    }
}

unix:!mac{
    LIBS += -L$$DESTDIR -lTTKUi -lTTKExtras -lzlib -lTTKZip
    QMAKE_CXXFLAGS += -std=c++11 -Wunused-function -Wswitch
}

DEFINES += TTK_LIBRARY

#########################################
HEADERS += $$PWD/downloadglobal.h
INCLUDEPATH += $$PWD
#########################################
include($$PWD/TTKThirdParty/TTKThirdParty.pri)
#########################################
include($$PWD/TTKModule/TTKModule.pri)
