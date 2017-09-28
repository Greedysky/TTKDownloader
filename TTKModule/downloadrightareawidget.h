#ifndef DOWNLOADRIGHTAREAWIDGET_H
#define DOWNLOADRIGHTAREAWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "downloadglobaldefine.h"

class DownloadListWidgets;
class DownloadHistoryRecordWidget;

namespace Ui {
    class DownloadApplication;
}

/*! @brief The class of the app right area widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_GUI_EXPORT DownloadRightAreaWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadRightAreaWidget(QWidget *parent = 0);

    ~DownloadRightAreaWidget();

    /*!
     * Init widget.
     */
    void init();
    /*!
     * Get class object name.
     */
    static QString getClassName();
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

protected:
    Ui::DownloadApplication *m_ui;

    DownloadListWidgets *m_listWidget;
    DownloadHistoryRecordWidget *m_historyWidget;

    static DownloadRightAreaWidget *m_instance;
};

#endif // DOWNLOADRIGHTAREAWIDGET_H
