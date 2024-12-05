#ifndef DOWNLOADWIDGETRENDERER_H
#define DOWNLOADWIDGETRENDERER_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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

#include <QLabel>
#include "ttkmoduleexport.h"

/*! @brief The class of the widget background renderer.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadWidgetRenderer
{
    TTK_DECLARE_MODULE(DownloadWidgetRenderer)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadWidgetRenderer();

    /*!
     * Set background label.
     */
    inline void setBackgroundLabel(QLabel *label) { m_background = label; }

protected:
    /*!
     * Set background pixmap.
     */
    void setBackgroundPixmap(const QSize &size);

private:
    QLabel *m_background;

};

#endif // DOWNLOADWIDGETRENDERER_H
