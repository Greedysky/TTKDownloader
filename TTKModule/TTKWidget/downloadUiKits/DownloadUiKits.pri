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
    $$PWD/downloaduiobject.h \
    $$PWD/downloadfunctionuiobject.h \
    $$PWD/downloadtinyuiobject.h
}

contains(CONFIG, TTK_BUILD_LIB){
FORMS    += \
    $$PWD/downloadapplication.ui \
    $$PWD/downloadbackgroundskindialog.ui \
    $$PWD/downloadnewfiledialog.ui \
    $$PWD/downloadcolordialog.ui \
    $$PWD/downloadmessagebox.ui \
    $$PWD/downloadmessageaboutdialog.ui \
    $$PWD/downloadsettingwidget.ui
}
