# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2020 Greedysky Studio
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

QT       += core network xml
unix:VERSION += 2.1.0.0

win32:TARGET = ../../../bin/TTKConsole
unix:TARGET = ../../lib/TTKConsole

TEMPLATE = app
CONFIG += console

UI_DIR = ./.build/ui
MOC_DIR = ./.build/moc
OBJECTS_DIR = ./.build/obj
RCC_DIR = ./.build/rcc

##openssl lib check
win32:{
    SSL_DEPANDS = $$OUT_PWD/../../bin/$$TTKDownloader/ssleay32.dll
    SSL_DEPANDS = $$replace(SSL_DEPANDS, /, \\)
    exists($$SSL_DEPANDS):LIBS += -L../../bin/$$TTKDownloader -lssl
}
unix:!mac{
    SSL_DEPANDS = $$OUT_PWD/../../lib/$$TTKDownloader/libssleay32.so
    exists($$SSL_DEPANDS):LIBS += -L../../lib/$$TTKDownloader -lssl
}

DEFINES += TTK_LIBRARY

win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

INCLUDEPATH += \
    ../ \
    ../../ \
    ../../TTKModule/TTKCore/downloadCoreKits \
    ../../TTKModule/TTKCore/downloadNetworkKits \
    ../../TTKModule/TTKCore/downloadUtilsKits

SOURCES += \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadabstractxml.cpp \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadbreakpointconfigmanager.cpp \
    ../../TTKModule/TTKCore/downloadNetworkKits/downloadthreadmanager.cpp \
    ../../TTKModule/TTKCore/downloadNetworkKits/downloadthread.cpp \
    ../../TTKModule/TTKCore/downloadNetworkKits/downloadurlencoder.cpp \
    ../../TTKModule/TTKCore/downloadUtilsKits/downloadcoreutils.cpp \
    downloadconsolemain.cpp \
    downloadconsoleobject.cpp

HEADERS += \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadsettingmanager.h \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadabstractxml.h \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadlogger.h \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadobject.h \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadglobaldefine.h \
    ../../TTKModule/TTKCore/downloadCoreKits/downloadbreakpointconfigmanager.h \
    ../../TTKModule/TTKCore/downloadNetworkKits/downloadthreadmanager.h \
    ../../TTKModule/TTKCore/downloadNetworkKits/downloadthread.h \
    ../../TTKModule/TTKCore/downloadNetworkKits/downloadurlencoder.h \
    ../../TTKModule/TTKCore/downloadUtilsKits/downloadcoreutils.h \
    ../downloadrunglobaldefine.h \
    downloadconsoleobject.h

win32{
    RC_FILE = TTKConsole.rc
}
