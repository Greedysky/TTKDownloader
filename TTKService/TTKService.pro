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

TEMPLATE = app

include($$PWD/../TTKDownloader.pri)

TARGET = TTKService

LIBS += -L$$DESTDIR -lTTKCore -lTTKDumper

INCLUDEPATH +=  \
    $$PWD/../TTKModule \
    $$PWD/../TTKModule/TTKCore/downloadCoreKits \
    $$PWD/../TTKModule/TTKWidget/downloadWidgetCoreKits

win32:msvc{
HEADERS += \
    $$PWD/../TTKModule/downloadapplication.h \
    $$PWD/../TTKModule/TTKWidget/downloadWidgetCoreKits/downloadabstractmoveresizewidget.h
}

SOURCES += $$PWD/downloadservicemain.cpp

win32:RC_FILE = $$PWD/TTKService.rc
