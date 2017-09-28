#ifndef DOWNLOADLISTITEMWIDGET_H
#define DOWNLOADLISTITEMWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QTimer>
#include <QWidget>
#include "downloadglobaldefine.h"

class QLabel;
class QProgressBar;

/*! @brief The class of the download list item widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadListItemWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadListItemWidget(QWidget *parent = 0);

    ~DownloadListItemWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();
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

    qint64 m_previousSize, m_totalSize;
    QTimer m_timer;

    QLabel *m_iconLabel, *m_fileNameLabel, *m_fileSizeLabel;
    QProgressBar *m_progressBar;
    QLabel *m_speedTimeLabel, *m_speedLabel, *m_stateLabel;

};

#endif // DOWNLOADLISTITEMWIDGET_H
