# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

TEMPLATE = lib
CONFIG += DOWNLOAD_BUILD_LIB

include(../TTKDownloader.pri)
unix:VERSION += $$TTKDownloader

win32:TARGET = ../../bin/$$TTKDownloader/TTKCore
unix:TARGET = ../lib/$$TTKDownloader/TTKCore

INCLUDEPATH += $$PWD

SOURCES += \
    downloadapplication.cpp \
    downloadapplicationobject.cpp \
    downloadbottomareawidget.cpp \
    downloadleftareawidget.cpp \
    downloadrightareawidget.cpp \
    downloadtopareawidget.cpp


HEADERS  += \
    downloadapplication.h \
    downloadapplicationobject.h \
    downloadbottomareawidget.h \
    downloadleftareawidget.h \
    downloadrightareawidget.h \
    downloadtopareawidget.h
    
    
win32{
    RC_FILE = TTKCore.rc
}
