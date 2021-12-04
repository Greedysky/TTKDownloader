#ifndef DOWNLOADWIDGETUTILS_H
#define DOWNLOADWIDGETUTILS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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
 ================================================= */

#include "ttkglobaldefine.h"

/*! @brief The class of the utils widget object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUtils
{
    namespace Widget
    {
        /*!
         * Set widget transparent.
         */
        TTK_MODULE_EXPORT void setTransparent(QWidget *widget, int alpha);
        /*!
         * Set fusion two image.
         */
        TTK_MODULE_EXPORT void fusionPixmap(QPixmap &bg, const QPixmap &fg, const QPoint &pt);
        /*!
         * Get pximap data.
         */
        TTK_MODULE_EXPORT QByteArray generatePixmapData(const QPixmap &pix);

        /*!
         * Rerender the custum value.
         */
        template <typename T>
        TTK_MODULE_EXPORT T reRenderValue(const T &key, const T &alpha, const T &value)
        {
            if(alpha < 0)
            {
                return 0;
            }
            else if(alpha > key)
            {
                return key;
            }
            return (key - alpha) * 1.0 / 100 * value + alpha;
        }

        /*!
        * Rerender the image by color burn transform.
        */
        TTK_MODULE_EXPORT void reRenderImage(qint64 &avg, int delta, const QImage *input, QImage *output);

        /*!
         * Get open file dialog.
         */
        TTK_MODULE_EXPORT QString openFileDialog(QWidget *obj);

    }
}

#endif // DOWNLOADWIDGETUTILS_H
