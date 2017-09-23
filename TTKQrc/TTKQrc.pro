# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

TEMPLATE = lib

include(../TTKVersion.pri)
unix:VERSION += $$TTKDownloader

win32:TARGET = ../../bin/$$TTKDownloader/TTKUi
unix:TARGET = ../lib/$$TTKDownloader/TTKUi

RESOURCES += \
    TTKDownloader.qrc
    
win32{
    RC_FILE = TTKQrc.rc
}
