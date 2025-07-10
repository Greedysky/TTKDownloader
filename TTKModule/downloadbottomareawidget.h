#ifndef DOWNLOADBOTTOMAREAWIDGET_H
#define DOWNLOADBOTTOMAREAWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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
#include <QSystemTrayIcon>
#include "downloadobject.h"
#include "ttkmoduleexport.h"

class DownloadSystemTrayMenu;
class DownloadNetworkSpeedThread;

namespace Ui {
    class DownloadApplication;
}

/*! @brief The class of the app bottom area widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBottomAreaWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBottomAreaWidget)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadBottomAreaWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadBottomAreaWidget();

    /*!
     * Get class object instance.
     */
    static DownloadBottomAreaWidget *instance();
    /*!
     * Set up app ui.
     */
    void setupUi(Ui::DownloadApplication *ui);

    /*!
     * Set system close config or not.
     */
    void setSystemCloseConfig(bool status) noexcept { m_systemCloseConfig = status;}
    /*!
     * Get system close config state.
     */
    bool systemCloseConfig() noexcept { return m_systemCloseConfig;}
    /*!
     * Get system tray visible state.
     */
    bool systemTrayIsVisible() noexcept { return m_systemTray->isVisible();}
    /*!
     * Set system tray message show title and context.
     */
    void showMessage(const QString &title, const QString &text);

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
    void settingButtonClicked();
    /*!
     * Download plan button clicked.
     */
    void planButtonClicked();
    /*!
     * Expand button clicked.
     */
    void expandButtonClicked();

private:
    /*!
     * Create system tray icon.
     */
    void createSystemTrayIcon();

    Ui::DownloadApplication *m_ui;
    bool m_isAvailable;
    bool m_systemCloseConfig;
    bool m_expandMode;
    QMenu *m_toolPopupMenu;
    QSystemTrayIcon *m_systemTray;
    DownloadSystemTrayMenu *m_systemTrayMenu;
    DownloadNetworkSpeedThread *m_speedThread;

    static DownloadBottomAreaWidget *m_instance;

};

#endif // DOWNLOADBOTTOMAREAWIDGET_H
