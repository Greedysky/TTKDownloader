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

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += TTKCommon TTKConfig TTKUi TTKThirdParty TTKModule TTKService TTKRun

TRANSLATIONS += $$PWD/TTKLanguage/cn.ts

##find translation module
unix:exists($$[QT_INSTALL_BINS]/lrelease){
    LRELEASE_EXECUTABLE = $$[QT_INSTALL_BINS]/lrelease
}

unix:exists($$[QT_INSTALL_BINS]/lrelease-qt5){
    LRELEASE_EXECUTABLE = $$[QT_INSTALL_BINS]/lrelease-qt5
}

win32:exists($$[QT_INSTALL_BINS]/lrelease.exe){
    LRELEASE_EXECUTABLE = $$[QT_INSTALL_BINS]/lrelease.exe
}

isEmpty(LRELEASE_EXECUTABLE){
    error(Could not find lrelease executable)
}else{
    message(Found lrelease executable: $$LRELEASE_EXECUTABLE)
}

include($$PWD/TTKVersion.pri)

unix{
    system($$PWD/TTKUtils/resource.sh $$PWD/TTKResource $$OUT_PWD/bin/$$TTK_VERSION)
    system($$PWD/TTKUtils/ts_unix.py $$LRELEASE_EXECUTABLE $$OUT_PWD/bin/$$TTK_VERSION $$PWD)
}

win32{
    output = $$OUT_PWD/bin/$$TTK_VERSION/GLanguage
    output = $$replace(output, /, \\)
    system($$PWD/TTKUtils/ts_win.bat $$LRELEASE_EXECUTABLE $$OUT_PWD/bin/$$TTK_VERSION $$PWD)
}
