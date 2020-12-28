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

!contains(CONFIG, TTK_NO_MSVC_LINK_NEED){
HEADERS  += \
    $$PWD/downloadbackgroundskindialog.h \
    $$PWD/downloadfuntionanimationwidget.h \
    $$PWD/downloadbackgroundlistwidget.h \
    $$PWD/downloadbackgroundpopwidget.h \
    $$PWD/downloadbackgroundremotewidget.h \
    $$PWD/downloadsystemtraymenu.h \
    $$PWD/downloadwindowextras.h \
    $$PWD/downloadnewfiledialog.h\
    $$PWD/downloadlistitemwidget.h \
    $$PWD/downloadlistwidgets.h \
    $$PWD/downloadfunctionlistwidget.h \
    $$PWD/downloadmessageaboutdialog.h \
    $$PWD/downloadsettingwidget.h \
    $$PWD/downloadhistoryrecordwidget.h

}

contains(CONFIG, TTK_BUILD_LIB){
SOURCES += \
    $$PWD/downloadbackgroundskindialog.cpp \
    $$PWD/downloadfuntionanimationwidget.cpp \
    $$PWD/downloadbackgroundpopwidget.cpp \
    $$PWD/downloadbackgroundlistwidget.cpp \
    $$PWD/downloadsystemtraymenu.cpp \
    $$PWD/downloadbackgroundremotewidget.cpp \
    $$PWD/downloadwindowextras.cpp \
    $$PWD/downloadnewfiledialog.cpp\
    $$PWD/downloadlistitemwidget.cpp \
    $$PWD/downloadlistwidgets.cpp \
    $$PWD/downloadfunctionlistwidget.cpp \
    $$PWD/downloadmessageaboutdialog.cpp \
    $$PWD/downloadsettingwidget.cpp \
    $$PWD/downloadhistoryrecordwidget.cpp

}
