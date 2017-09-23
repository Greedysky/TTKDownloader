#ifndef DOWNLOADWINDOWEXTRAS_H
#define DOWNLOADWINDOWEXTRAS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QObject>
#include "downloadobject.h"
#include "downloadglobaldefine.h"

#if defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
class DownloadApplication;
class QWinTaskbarButton;
class QWinTaskbarProgress;
class QWinThumbnailToolBar;
class QWinThumbnailToolButton;
#endif

/*! @brief The class of the windows extras.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadWindowExtras : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadWindowExtras(QObject *parent = 0);

    ~DownloadWindowExtras();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Set current play state button.
     */
    void showPlayStatus(bool status) const;
    /*!
     * Set current value.
     */
    void setValue(int value) const;
    /*!
     * Set current range from start to end.
     */
    void setRange(int start, int end) const;
    /*!
     * Enable or disable blur behind window.
     */
    void disableBlurBehindWindow(bool enable);
    /*!
     * Get blur behind window state.
     */
    inline bool isDisableBlurBehindWindow() const { return m_disableBlurBehindWindow; }

protected:
#if defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
    /*!
     * Create jump list.
     */
    void createJumpList() const;
    /*!
     * Create taskbar.
     */
    void createTaskbar();

    DownloadApplication *m_superClass;
    QWinTaskbarButton *m_taskbarButton;
    QWinTaskbarProgress *m_taskbarProgress;
#endif
    bool m_disableBlurBehindWindow;

};

#endif // DOWNLOADWINDOWEXTRAS_H
