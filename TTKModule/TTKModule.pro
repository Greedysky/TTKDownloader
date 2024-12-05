# ***************************************************************************
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2025 Greedysky Studio
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
CONFIG += plugin lib

include($$PWD/TTKModule.pri)
include($$PWD/../TTKDownloader.pri)

TARGET = TTKCore

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/downloadapplication.h \
    $$PWD/downloadapplicationmodule.h \
    $$PWD/downloadbottomareawidget.h \
    $$PWD/downloadleftareawidget.h \
    $$PWD/downloadrightareawidget.h \
    $$PWD/downloadtopareawidget.h

SOURCES += \
    $$PWD/downloadapplication.cpp \
    $$PWD/downloadapplicationmodule.cpp \
    $$PWD/downloadbottomareawidget.cpp \
    $$PWD/downloadleftareawidget.cpp \
    $$PWD/downloadrightareawidget.cpp \
    $$PWD/downloadtopareawidget.cpp

win32:RC_FILE = $$PWD/$${TARGET}.rc
