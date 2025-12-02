#ifndef DOWNLOADAPPLICATIONMODULE_H
#define DOWNLOADAPPLICATIONMODULE_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2026 Greedysky Studio

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

#include "downloadobject.h"
#include "ttkmoduleexport.h"

class QPropertyAnimation;

/*! @brief The class of the app object module.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadApplicationModule : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadApplicationModule(QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadApplicationModule();

    /*!
     * Get class object instance.
     */
    static DownloadApplicationModule *instance();

public Q_SLOTS:
    /*!
     * Application quit.
     */
    void quit();
    /*!
     * Window close animation.
     */
    void windowCloseAnimation();
    /*!
     * Show about widget.
     */
    void showAboutWidget();
    /*!
     * Reset current window geometry.
     */
    void resetWindowGeometry();

private:
    QPropertyAnimation *m_quitAnimation;

    static DownloadApplicationModule *m_instance;
};

#endif // DOWNLOADAPPLICATIONMODULE_H
