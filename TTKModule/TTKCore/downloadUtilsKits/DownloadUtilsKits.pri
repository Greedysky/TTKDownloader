# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

INCLUDEPATH += $$PWD

!contains(CONFIG, DOWNLOAD_NO_MSVC_LINK_NEED){
HEADERS  += \
    $$PWD/downloadalgorithmutils.h \
    $$PWD/downloadcoreutils.h \
    $$PWD/downloadnumberutils.h \
    $$PWD/downloadstringutils.h \
    $$PWD/downloadwidgetutils.h

}

contains(CONFIG, DOWNLOAD_BUILD_LIB){
SOURCES += \
    $$PWD/downloadalgorithmutils.cpp \
    $$PWD/downloadcoreutils.cpp \
    $$PWD/downloadnumberutils.cpp \
    $$PWD/downloadstringutils.cpp \
    $$PWD/downloadwidgetutils.cpp

}
