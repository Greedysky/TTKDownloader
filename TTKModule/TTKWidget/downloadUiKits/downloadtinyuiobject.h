#ifndef DOWNLOADTINYUIOBJECT_H
#define DOWNLOADTINYUIOBJECT_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2024 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QObject>

/*! @brief The namespace of the tiny button style.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace UI
    {
        static constexpr const char *THDSkin = " \
            QToolButton{ border:none; \
            background-image:url(:/tiny/btn_skin_normal); } \
            QToolButton:hover{ background-image:url(:/tiny/btn_skin_hover); }";

        static constexpr const char *THDSetting = " \
            QToolButton{ border:none; \
            background-image:url(:/tiny/btn_setting_normal); } \
            QToolButton:hover{ background-image:url(:/tiny/btn_setting_hover); }";

        static constexpr const char *THDMinimum = " \
            QToolButton{ border:none; \
            background-image:url(:/tiny/btn_min_normal); } \
            QToolButton:hover{ background-image:url(:/tiny/btn_min_hover); }";

        static constexpr const char *THDMaximum = " \
            QToolButton{ border:none; \
            background-image:url(:/tiny/btn_max_normal); } \
            QToolButton:hover{ background-image:url(:/tiny/btn_max_hover); }";

        static constexpr const char *THDClose = " \
            QToolButton{ border:none; \
            background-image:url(:/tiny/btn_close_normal); } \
            QToolButton:hover{ background-image:url(:/tiny/btn_close_hover); }";

    }
}

#endif // DOWNLOADTINYUIOBJECT_H
