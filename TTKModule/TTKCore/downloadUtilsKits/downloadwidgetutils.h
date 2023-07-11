#ifndef DOWNLOADWIDGETUTILS_H
#define DOWNLOADWIDGETUTILS_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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

#include "ttkglobaldefine.h"

class QMenu;

/*! @brief The namespace of the utils widget.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace Widget
    {
        /*!
         * Adjust the menu position.
         */
        TTK_MODULE_EXPORT void adjustMenuPosition(QMenu *menu);
        /*!
         * Adjust the widget in screen center.
         */
        TTK_MODULE_EXPORT void adjustWidgetPosition(QWidget *widget);

        /*!
         * Set widget transparent.
         */
        TTK_MODULE_EXPORT void setTransparent(QWidget *widget, int alpha);
        /*!
         * Set widget transparent.
         */
        TTK_MODULE_EXPORT void setTransparent(QWidget *widget, const QColor &color);

        /*!
         * Generate vertical scrollArea format style.
         */
        TTK_MODULE_EXPORT void generateVScrollAreaFormat(QWidget *widget, QWidget *parent, bool background = true);
        /*!
         * Generate horizontal scrollArea format style.
         */
        TTK_MODULE_EXPORT void generateHScrollAreaFormat(QWidget *widget, QWidget *parent, bool background = true);
    }
}

#endif // DOWNLOADWIDGETUTILS_H
