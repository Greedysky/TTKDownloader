# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

contains(CONFIG, DOWNLOAD_BUILD_LIB){
    include($$PWD/downloadUiKits/DownloadUiKits.pri)
}
include($$PWD/downloadWidgetKits/DownloadWidgetKits.pri)
include($$PWD/downloadWidgetCoreKits/DownloadWidgetCoreKits.pri)
