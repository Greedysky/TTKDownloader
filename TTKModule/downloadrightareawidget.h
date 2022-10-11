#ifndef DOWNLOADRIGHTAREAWIDGET_H
#define DOWNLOADRIGHTAREAWIDGET_H

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
#include "ttkglobaldefine.h"

class DownloadListWidgets;
class DownloadHistoryRecordWidget;

namespace Ui {
    class DownloadApplication;
}

/*! @brief The class of the app right area widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadRightAreaWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadRightAreaWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadRightAreaWidget(QWidget *parent = nullptr);
    ~DownloadRightAreaWidget();

    /*!
     * Init widget.
     */
    void initialize();

    /*!
     * Get class object instance.
     */
    static DownloadRightAreaWidget *instance();
    /*!
     * Set up app ui.
     */
    void setupUi(Ui::DownloadApplication* ui);

    /*!
     * Resize window bound by widgte resize called.
     */
    void resizeWindow();

public Q_SLOTS:
    /*!
     * Download state changed.
     */
    void downloadStateChanged(bool state);
    /*!
     * Shown new file dialog.
     */
    void showNewFileDialog();
    /*!
     * Start to download.
     */
    void startToDownload();
    /*!
     * Stop to download.
     */
    void stopToDownload();
    /*!
     * Sselect all mode.
     */
    void editSelectAll();
    /*!
     * Reverse select mode.
     */
    void editReverseSelect();

private:
    Ui::DownloadApplication *m_ui;

    DownloadListWidgets *m_listWidget;
    DownloadHistoryRecordWidget *m_historyWidget;

    static DownloadRightAreaWidget *m_instance;

};

#endif // DOWNLOADRIGHTAREAWIDGET_H
