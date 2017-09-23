#ifndef DOWNLOADTINYUIOBJECT_H
#define DOWNLOADTINYUIOBJECT_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QObject>

/*! @brief The namespace of the tiny button style.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUIObject
{
    const QString MTHDSkin = " \
            QToolButton{ border:none; \
            background-image: url(:/tiny/btn_skin_normal);} \
            QToolButton:hover{ background-image: url(:/tiny/btn_skin_hover);}";

    const QString MTHDSetting = " \
            QToolButton{ border:none; \
            background-image: url(:/tiny/btn_setting_normal);} \
            QToolButton:hover{ background-image: url(:/tiny/btn_setting_hover);}";

    const QString MTHDMinimum = " \
            QToolButton{ border:none; \
            background-image: url(:/tiny/btn_min_normal);} \
            QToolButton:hover{ background-image: url(:/tiny/btn_min_hover);}";

    const QString MTHDMaximum = " \
            QToolButton{ border:none; \
            background-image: url(:/tiny/btn_max_normal);} \
            QToolButton:hover{ background-image: url(:/tiny/btn_max_hover);}";

    const QString MTHDClose = " \
            QToolButton{ border:none; \
            background-image: url(:/tiny/btn_close_normal);} \
            QToolButton:hover{ background-image: url(:/tiny/btn_close_hover);}";

}

#endif // DOWNLOADTINYUIOBJECT_H
