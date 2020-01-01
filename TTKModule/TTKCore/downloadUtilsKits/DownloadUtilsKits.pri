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

INCLUDEPATH += $$PWD

!contains(CONFIG, TTK_NO_MSVC_LINK_NEED){
HEADERS  += \
    $$PWD/downloadalgorithmutils.h \
    $$PWD/downloadcoreutils.h \
    $$PWD/downloadnumberutils.h \
    $$PWD/downloadstringutils.h \
    $$PWD/downloadwidgetutils.h \
    $$PWD/downloadurlutils.h \
    $$PWD/downloadcodecutils.h
    
}

contains(CONFIG, TTK_BUILD_LIB){
SOURCES += \
    $$PWD/downloadalgorithmutils.cpp \
    $$PWD/downloadcoreutils.cpp \
    $$PWD/downloadnumberutils.cpp \
    $$PWD/downloadstringutils.cpp \
    $$PWD/downloadwidgetutils.cpp \
    $$PWD/downloadurlutils.cpp \
    $$PWD/downloadcodecutils.cpp
    
}
