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

INCLUDEPATH += $$PWD

HEADERS  += \
    $$PWD/downloadobject.h \
    $$PWD/downloadnumberdefine.h \
    $$PWD/downloadabstractxml.h \
    $$PWD/downloadbackgroundconfigmanager.h \
    $$PWD/downloadbackgroundmanager.h \
    $$PWD/downloadcryptographichash.h \
    $$PWD/downloadextractwrapper.h \
    $$PWD/downloadhotkeymanager.h \
    $$PWD/downloadlicensecore.h \
    $$PWD/downloadotherdefine.h \
    $$PWD/downloadsettingmanager.h \
    $$PWD/downloadsysconfigmanager.h \
    $$PWD/downloadruntimemanager.h \
    $$PWD/downloadtime.h \
    $$PWD/downloadbreakpointconfigmanager.h \
    $$PWD/downloadrecordconfigmanager.h \
    $$PWD/downloadlistconfigmanager.h

SOURCES += \
    $$PWD/downloadabstractxml.cpp \
    $$PWD/downloadbackgroundconfigmanager.cpp \
    $$PWD/downloadbackgroundmanager.cpp \
    $$PWD/downloadcryptographichash.cpp \
    $$PWD/downloadextractwrapper.cpp \
    $$PWD/downloadhotkeymanager.cpp \
    $$PWD/downloadlicensecore.cpp \
    $$PWD/downloadsysconfigmanager.cpp \
    $$PWD/downloadruntimemanager.cpp \
    $$PWD/downloadtime.cpp \
    $$PWD/downloadbreakpointconfigmanager.cpp \
    $$PWD/downloadrecordconfigmanager.cpp \
    $$PWD/downloadlistconfigmanager.cpp
