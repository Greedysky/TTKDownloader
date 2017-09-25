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
    $$PWD/downloaduiobject.h \
    $$PWD/downloadfunctionuiobject.h \
    $$PWD/downloadtinyuiobject.h
}

FORMS    += \
    $$PWD/downloadapplication.ui \
    $$PWD/downloadbackgroundskindialog.ui \
    $$PWD/downloadnewfiledialog.ui \
    $$PWD/downloadcolordialog.ui \
    $$PWD/downloadmessagebox.ui \
    $$PWD/downloadmessageaboutdialog.ui \
    $$PWD/downloadsettingwidget.ui
