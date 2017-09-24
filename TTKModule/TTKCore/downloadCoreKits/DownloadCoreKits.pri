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
    $$PWD/downloadlogger.h \
    $$PWD/downloadglobaldefine.h \
    $$PWD/downloadobject.h \
    $$PWD/downloadnumberdefine.h \
    $$PWD/downloadabstractxml.h \
    $$PWD/downloadbackgroundconfigmanager.h \
    $$PWD/downloadbackgroundmanager.h \
    $$PWD/downloadcryptographichash.h \
    $$PWD/downloadextractwrap.h \
    $$PWD/downloadhotkeymanager.h \
    $$PWD/downloadlicensecore.h \
    $$PWD/downloadotherdefine.h \
    $$PWD/downloadsettingmanager.h \
    $$PWD/downloadsingleton.h \
    $$PWD/downloadsysconfigmanager.h \
    $$PWD/downloadruntimemanager.h \
    $$PWD/downloadtime.h \
    $$PWD/downloadbreakpointconfigmanager.h

}

contains(CONFIG, DOWNLOAD_BUILD_LIB){
SOURCES += \
    $$PWD/downloadabstractxml.cpp \
    $$PWD/downloadbackgroundconfigmanager.cpp \
    $$PWD/downloadbackgroundmanager.cpp \
    $$PWD/downloadcryptographichash.cpp \
    $$PWD/downloadextractwrap.cpp \
    $$PWD/downloadhotkeymanager.cpp \
    $$PWD/downloadlicensecore.cpp \
    $$PWD/downloadsysconfigmanager.cpp \
    $$PWD/downloadruntimemanager.cpp \
    $$PWD/downloadtime.cpp \
    $$PWD/downloadbreakpointconfigmanager.cpp

}
