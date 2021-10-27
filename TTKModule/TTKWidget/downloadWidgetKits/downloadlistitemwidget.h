#ifndef DOWNLOADLISTITEMWIDGET_H
#define DOWNLOADLISTITEMWIDGET_H

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

#include <QTimer>
#include <QWidget>
#include "ttkglobaldefine.h"

class QLabel;
class QProgressBar;

/*! @brief The class of the download list item widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadListItemWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadListItemWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadListItemWidget(QWidget *parent = nullptr);
    ~DownloadListItemWidget();

    /*!
     * Get progress bar percent.
     */
    float getPercent() const;

public Q_SLOTS:
    /*!
     * Background image changed.
     */
    void backgroundChanged();
    /*!
     * Download progress changed.
     */
    void progressChanged(qint64 current, qint64 total);
    /*!
     * Update file info changed.
     */
    void updateFileInfoChanged(const QString &name, qint64 size);
    /*!
     * Download state changed.
     */
    void stateChanged(const QString &state);

private Q_SLOTS:
    /*!
     * Update download speed.
     */
    void updateDownloadSpeed();

protected:
    /*!
     * Update download left time.
     */
    QString timeStandardization(qint64 time);

    qint64 m_currentSize, m_previousSize, m_totalSize;
    QTimer m_timer;

    QLabel *m_iconLabel, *m_fileNameLabel, *m_fileSizeLabel;
    QProgressBar *m_progressBar;
    QLabel *m_speedTimeLabel, *m_speedLabel, *m_stateLabel;

};

#endif // DOWNLOADLISTITEMWIDGET_H
