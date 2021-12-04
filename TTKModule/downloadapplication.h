#ifndef DOWNLOADAPPLICATION_H
#define DOWNLOADAPPLICATION_H

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

#include "downloadabstractmoveresizewidget.h"

class DownloadBottomAreaWidget;
class DownloadTopAreaWidget;
class DownloadRightAreaWidget;
class DownloadLeftAreaWidget;
class DownloadApplicationObject;

namespace Ui {
class DownloadApplication;
}

/*! @brief The class of the app main widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadApplication : public DownloadAbstractMoveResizeWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadApplication)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadApplication(QWidget *parent = nullptr);
    ~DownloadApplication();

    /*!
     * Get class object instance.
     */
    static DownloadApplication *instance();

public Q_SLOTS:
    /*!
     * Get settings parameters.
     */
    void parameterSetting();
    /*!
     * Show maximized window.
     */
    void showMaximizedWindow();
    /*!
     * Application window close.
     */
    void quitWindowClose();
    /*!
     * Create right menu.
     */
    void appCreateRightMenu();

private:
    /*!
     * Override the widget event.
     */
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    /*!
     * Read XML config from text.
     */
    void readXMLConfigFromText();
    /*!
     * Write XML config to text.
     */
    void writeXMLConfigToText();

    Ui::DownloadApplication *m_ui;

    DownloadBottomAreaWidget *m_bottomAreaWidget;
    DownloadTopAreaWidget *m_topAreaWidget;
    DownloadRightAreaWidget *m_rightAreaWidget;
    DownloadLeftAreaWidget *m_leftAreaWidget;
    DownloadApplicationObject *m_applicationObject;

    static DownloadApplication *m_instance;
};

#endif // DOWNLOADAPPLICATION_H
