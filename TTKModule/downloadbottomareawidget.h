#ifndef DOWNLOADBOTTOMAREAWIDGET_H
#define DOWNLOADBOTTOMAREAWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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

#include <QWidget>
#include <QSystemTrayIcon>
#include "downloadobject.h"
#include "downloadglobaldefine.h"

class DownloadSystemTrayMenu;
class DownloadWindowExtras;
class DownloadNetworkSpeedTestThread;

namespace Ui {
    class DownloadApplication;
}

/*! @brief The class of the app bottom area widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_GUI_EXPORT DownloadBottomAreaWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBottomAreaWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBottomAreaWidget(QWidget *parent = nullptr);

    ~DownloadBottomAreaWidget();

    /*!
     * Get class object instance.
     */
    static DownloadBottomAreaWidget *instance();
    /*!
     * Set up app ui.
     */
    void setupUi(Ui::DownloadApplication* ui);

    /*!
     * Set system close config or not.
     */
    void setSystemCloseConfig(bool status) { m_systemCloseConfig = status;}
    /*!
     * Get system close config state.
     */
    bool getSystemCloseConfig() { return m_systemCloseConfig;}
    /*!
     * Get system tray visible state.
     */
    bool systemTrayIsVisible() { return m_systemTray->isVisible();}
    /*!
     * Set system tray message show title and context.
     */
    void showMessage(const QString &title, const QString &text);

#if defined TTK_DEBUG && defined Q_OS_WIN && defined TTK_GREATER_NEW
    /*!
     * Set current value.
     */
    void setValue(int value) const;
    /*!
     * Set current range from start to end.
     */
    void setRange(int min, int max) const;
#endif

public Q_SLOTS:
    /*!
     * System tray icon activate.
     */
    void iconActivated(QSystemTrayIcon::ActivationReason);
    /*!
     * Send current upload and download speed data.
     */
    void updateNetworkData(ulong upload, ulong download);
    /*!
     * Download setting button clicked.
     */
    void downloadSettingButtonClicked();
    /*!
     * Download plan button clicked.
     */
    void downloadPlanButtonClicked();
    /*!
     * Expand button clicked.
     */
    void expandButtonClicked();

protected:
    /*!
     * Create system tray icon.
     */
    void createSystemTrayIcon();

    Ui::DownloadApplication *m_ui;
    bool m_systemCloseConfig;

    QMenu *m_toolPopupMenu;
    QSystemTrayIcon *m_systemTray;
    DownloadSystemTrayMenu *m_systemTrayMenu;
    DownloadWindowExtras *m_windowExtras;
    DownloadNetworkSpeedTestThread *m_speedThread;

    static DownloadBottomAreaWidget *m_instance;
};

#endif // DOWNLOADBOTTOMAREAWIDGET_H
