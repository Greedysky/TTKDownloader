#ifndef DOWNLOADUNITS_H
#define DOWNLOADUNITS_H

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

class DownloadThreadManager;
class DownloadListItemWidget;

/*! @brief The class of the download thread manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadUnits : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadUnits(const QString &url, QObject *parent = nullptr);
    DownloadUnits(const QString &url, const QString &name, QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadUnits();

    /*!
     * Get download list item widget.
     */
    DownloadListItemWidget* widget() const noexcept;

    /*!
     * Start to download.
     */
    void start();
    /*!
     * Pause to download.
     */
    void pause();
    /*!
     * Queue to download.
     */
    void queue();

    /*!
     * Get download running state.
     */
    bool isRunning() const noexcept;
    /*!
     * Get download state.
     */
    TTK::DownloadState state() const noexcept;

    /*!
     * Get download url.
     */
    inline QString url() const noexcept { return m_url; }
    /*!
     * Get download name.
     */
    inline QString name() const noexcept { return m_name; }
    /*!
     * Get download path.
     */
    inline QString path() const noexcept { return m_path; }

Q_SIGNALS:
    /*!
     * Remove current item widget.
     */
    void removeItemWidget(DownloadUnits *unit);

private Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    void downloadFinished(const QString &path);

private:
    bool m_pause;
    QString m_url, m_name, m_path;
    DownloadListItemWidget *m_item;
    DownloadThreadManager *m_manager;

};

#endif // DOWNLOADUNITS_H
