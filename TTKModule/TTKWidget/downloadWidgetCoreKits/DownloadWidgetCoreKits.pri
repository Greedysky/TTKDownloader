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
    $$PWD/downloadabstractmovedialog.h \
    $$PWD/downloadabstractmovewidget.h \
    $$PWD/downloadabstracttablewidget.h \
    $$PWD/downloadabstractmoveresizewidget.h \
    $$PWD/downloadanimationstackedwidget.h \
    $$PWD/downloadtransitionanimationlabel.h \
    $$PWD/downloadclickedslider.h \
    $$PWD/downloadcolordialog.h \
    $$PWD/downloadmessagebox.h \
    $$PWD/downloadtoolmenuwidget.h \
    $$PWD/downloadtoollabelbutton.h

}

contains(CONFIG, DOWNLOAD_BUILD_LIB){
SOURCES += \
    $$PWD/downloadabstractmovedialog.cpp \
    $$PWD/downloadabstractmovewidget.cpp \
    $$PWD/downloadabstracttablewidget.cpp \
    $$PWD/downloadabstractmoveresizewidget.cpp \
    $$PWD/downloadanimationstackedwidget.cpp \
    $$PWD/downloadtransitionanimationlabel.cpp \
    $$PWD/downloadclickedslider.cpp \
    $$PWD/downloadmessagebox.cpp \
    $$PWD/downloadcolordialog.cpp \
    $$PWD/downloadtoolmenuwidget.cpp \
    $$PWD/downloadtoollabelbutton.cpp

}
