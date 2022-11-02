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

TEMPLATE = lib
CONFIG += warn_off plugin lib

include($$PWD/../../../TTKVersion.pri)

DESTDIR = $$OUT_PWD/../../../bin/$$TTKVersion
TARGET = TTKZip

DEFINES += \
    ZLIB_DLL \
    ZLIB_INTERNAL

LIBS += -L$$DESTDIR -lzlib

INCLUDEPATH += $$PWD/../

HEADERS += \
    $$PWD/zip.h \
    $$PWD/unzip.h \
    $$PWD/mztools.h \
    $$PWD/ioapi.h \
    $$PWD/crypt.h

SOURCES += \
    $$PWD/zip.c \
    $$PWD/unzip.c \
    $$PWD/mztools.c \
    $$PWD/ioapi.c

win32{
    HEADERS += $$PWD/iowin32.h
    SOURCES += $$PWD/iowin32.c
    RC_FILE = $$PWD/ttkzip.rc
}
