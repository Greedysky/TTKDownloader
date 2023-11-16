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

#include "ttkmoduleexport.h"
#include "ttknumberdefine.h"

/*! @brief The namespace of the utils image.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace Image
    {
        /*!
         * Set fusion two image.
         */
        TTK_MODULE_EXPORT void fusionPixmap(QPixmap &back, const QPixmap &front, const QPoint &pt);
        /*!
         * Get pximap data.
         */
        TTK_MODULE_EXPORT QByteArray generatePixmapData(const QPixmap &input);

        /*!
         * Rerender the custum value.
         */
        template <typename T>
        TTK_MODULE_EXPORT T reRenderValue(const T &key, const T &alpha, const T &value)
        {
            if(alpha < TTK_RN_MIN)
            {
                return TTK_RN_MIN;
            }
            else if(alpha > key)
            {
                return key;
            }
            return (key - alpha) * 1.0 / TTK_RN_MAX * value + alpha;
        }

        /*!
        * Rerender the image by color burn transform.
        */
        TTK_MODULE_EXPORT void reRenderImage(qint64 &avg, int delta, const QImage *input, QImage *output);

    }
}

#endif // DOWNLOADWIDGETUTILS_H
