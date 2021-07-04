#ifndef DOWNLOADAPPLICATIONOBJECT_H
#define DOWNLOADAPPLICATIONOBJECT_H

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

#include "downloadobject.h"
#include "ttkglobaldefine.h"

class QPropertyAnimation;

/*! @brief The class of the app object widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadApplicationObject : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadApplicationObject)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadApplicationObject(QObject *parent = nullptr);
    ~DownloadApplicationObject();

    /*!
     * Get class object instance.
     */
    static DownloadApplicationObject *instance();

public Q_SLOTS:
    /*!
     * Window close animation.
     */
    void windowCloseAnimation();
    /*!
     * Show about us widget.
     */
    void appAboutUs();
    /*!
     * Show version update widget.
     */
    void appVersionUpdate();
    /*!
     * Reset current window geometry.
     */
    void appResetWindow();

private:
    /*!
     * Something temp clean up.
     */
    void cleanUp();

    QPropertyAnimation *m_animation;

    static DownloadApplicationObject *m_instance;
};

#endif // DOWNLOADAPPLICATIONOBJECT_H
