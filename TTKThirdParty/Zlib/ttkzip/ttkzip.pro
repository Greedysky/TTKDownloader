# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

TEMPLATE = lib

include(../../../TTKVersion.pri)

win32:TARGET = ../../../../bin/$$TTKDownloader/TTKZip
unix:TARGET = ../../../lib/$$TTKDownloader/TTKZip

CONFIG       += warn_off
unix:VERSION += 1.0.0

DEFINES += \
    ZLIB_DLL \
    ZLIB_INTERNAL

INCLUDEPATH += $$PWD/../

win32{
    LIBS += -L../../../bin/$$TTKDownloader -lzlib
    HEADERS  += $$PWD/iowin32.h
    SOURCES += $$PWD/iowin32.c
}
unix:!mac{
    LIBS += -L../../../lib/$$TTKDownloader -lzlib
}

HEADERS  += \
    $$PWD/zip.h \
    $$PWD/unzip.h \
    $$PWD/mztools.h \
    $$PWD/ioapi.h \
    $$PWD/crypt.h

SOURCES += \
    $$PWD/zip.c \
    $$PWD/unzip.c \
    $$PWD/mztools.c \
    $$PWD/ioapi.c
    
win32{
    RC_FILE = ttkzip.rc
}
