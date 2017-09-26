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
    $$PWD/downloadthread.h \
    $$PWD/downloadunits.h \
    $$PWD/downloadthreadmanager.h\
    $$PWD/downloadbackgroundremotethread.h \
    $$PWD/downloadqueuecache.h \
    $$PWD/downloadsourcethread.h \
    $$PWD/downloadthreadabstract.h \
    $$PWD/downloadnetworkabstract.h \
    $$PWD/downloadnetworkthread.h \
    $$PWD/downloadnetworkspeedtestthread.h \
    $$PWD/downloadurlencoder.h

}

contains(CONFIG, DOWNLOAD_BUILD_LIB){
SOURCES += \
    $$PWD/downloadthread.cpp \
    $$PWD/downloadunits.cpp \
    $$PWD/downloadthreadmanager.cpp\
    $$PWD/downloadbackgroundremotethread.cpp \
    $$PWD/downloadqueuecache.cpp \
    $$PWD/downloadsourcethread.cpp \
    $$PWD/downloadthreadabstract.cpp \
    $$PWD/downloadnetworkabstract.cpp \
    $$PWD/downloadnetworkthread.cpp \
    $$PWD/downloadnetworkspeedtestthread.cpp \
    $$PWD/downloadurlencoder.cpp
    
}
