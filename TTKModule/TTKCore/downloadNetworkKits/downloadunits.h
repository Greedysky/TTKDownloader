#ifndef DOWNLOADUNITS_H
#define DOWNLOADUNITS_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2022 Greedysky Studio

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

class DownloadThreadManager;
class DownloadListItemWidget;

/*! @brief The class of download thread manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadUnits : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadUnits)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadUnits(const QString &url, QObject *parent = nullptr);
    ~DownloadUnits();

    /*!
     * Get download list item widget.
     */
    DownloadListItemWidget* downloadItemWidget();

    /*!
     * Pause to download.
     */
    void pause();
    /*!
     * Start to download.
     */
    void start(const QString &name = QString());

    /*!
     * Get download state.
     */
    int state() const;
    /*!
     * Get download url.
     */
    inline QString url() const { return m_url; }
    /*!
     * Get download path.
     */
    inline QString downloadedPath() const { return m_path; }
    /*!
     * Set download state changed.
     */
    void setStateChanged(const QString &state);

Q_SIGNALS:
    /*!
     * Remove current item widget.
     */
    void removeItemWidget(DownloadUnits *unit);

private Q_SLOTS:
    /*!
     * Download finished.
     */
    void downloadingFinished(const QString &path);

protected:
    bool m_pause;
    QString m_url, m_path;
    DownloadListItemWidget* m_downloadItem;
    DownloadThreadManager* m_downloadThread;

};

#endif // DOWNLOADUNITS_H
