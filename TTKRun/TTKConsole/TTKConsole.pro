# ***************************************************************************
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2022 Greedysky Studio
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
# ***************************************************************************

QT += core network xml

include($$PWD/../../TTKVersion.pri)

DESTDIR = $$OUT_PWD/../../bin
TARGET = TTKConsole

TEMPLATE = app
DEFINES += TTK_LIBRARY

CONFIG += console

##openssl lib check
win32{
    SSL_DEPANDS = $$OUT_PWD/../../bin/$$TTKVersion/ssleay32.dll
    SSL_DEPANDS = $$replace(SSL_DEPANDS, /, \\)
    exists($$SSL_DEPANDS):LIBS += -L../../bin/$$TTKVersion -lssl
}
unix:!mac{
    SSL_DEPANDS = $$OUT_PWD/../../bin/$$TTKVersion/libssleay32.so
    exists($$SSL_DEPANDS):LIBS += -L../../bin/$$TTKVersion -lssl
}

LIBS += -L$$DESTDIR/$$TTKVersion -lTTKCore
unix:LIBS += -L$$DESTDIR/$$TTKVersion -lTTKLibrary -lTTKUi -lTTKExtras -lzlib -lTTKZip

win32:msvc{
    CONFIG += c++11

HEADERS += \
    $$PWD/../../TTKModule/TTKCore/downloadNetworkKits/downloadthread.h \
    $$PWD/../../TTKModule/TTKCore/downloadNetworkKits/downloadthreadmanager.h \
    $$PWD/../../TTKModule/TTKCore/downloadCoreKits/downloadsettingmanager.h

}else{
    equals(QT_MAJOR_VERSION, 6){ #Qt6
        QMAKE_CXXFLAGS += -std=c++17
    }else{
        QMAKE_CXXFLAGS += -std=c++11
    }
}

INCLUDEPATH += \
    $$PWD/../ \
    $$PWD/../../TTKCommon \
    $$PWD/../../TTKModule/TTKCore/downloadCoreKits \
    $$PWD/../../TTKModule/TTKCore/downloadNetworkKits

HEADERS += $$PWD/downloadconsoleobject.h

SOURCES += \
    $$PWD/downloadconsolemain.cpp \
    $$PWD/downloadconsoleobject.cpp

win32:RC_FILE = $$PWD/TTKConsole.rc
