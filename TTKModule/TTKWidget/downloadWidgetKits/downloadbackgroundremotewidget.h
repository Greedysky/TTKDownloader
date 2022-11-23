#ifndef DOWNLOADBACKGROUNDREMOTEWIDGET_H
#define DOWNLOADBACKGROUNDREMOTEWIDGET_H

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

#include <QWidget>
#include "downloadbackgroundlistwidget.h"
#include "downloadbackgroundremotethread.h"

class QPushButton;
class QListWidgetItem;
class DownloadQueueCache;

/*! @brief The class of the remote background widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBackgroundRemoteWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBackgroundRemoteWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBackgroundRemoteWidget(QWidget *parent = nullptr);
    ~DownloadBackgroundRemoteWidget();

    /*!
     * Init the current download object.
     */
    void initialize();
    /*!
     * Abort the current download thread.
     */
    void abort();

    /*!
     * Create functions widget.
     */
    QWidget* createFunctionsWidget(bool revert, QWidget *object = 0);
    /*!
     * Output remote skin.
     */
    void outputRemoteSkin(DownloadBackgroundImage &image, const QString &data);

Q_SIGNALS:
    /*!
     * Reset the current bg when user click remote bg.
     */
    void showCustomSkin(const QString &path);

public Q_SLOTS:
    /*!
     * Remote bg type selected by index.
     */
    void buttonClicked(int index);
    /*!
     * Send download data from net.
     */
    void downLoadDataChanged(const QString &data);
    /*!
     * Send download data from net.
     */
    void downLoadDataChanged(const DownloadSkinRemoteGroupList &data);

private:
    /*!
     * Create button.
     */
    QPushButton *createButton(const QString &name);
    /*!
     * Button style changed.
     */
    void buttonStyleChanged();

    int m_currentIndex;
    QWidget *m_functionsWidget;
    QList<QPushButton*> m_functionsItems;
    DownloadSkinRemoteGroupList m_groups;
    DownloadBackgroundListWidget *m_listWidget;
    DownloadQueueCache *m_downloadQueue;
    DownloadBackgroundRemoteThread *m_queryThread;

};

#endif // DOWNLOADBACKGROUNDREMOTEWIDGET_H
