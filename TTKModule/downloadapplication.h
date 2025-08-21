#ifndef DOWNLOADAPPLICATION_H
#define DOWNLOADAPPLICATION_H

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

#include "downloadobject.h"
#include "ttkabstractmoveresizewidget.h"

class DownloadBottomAreaWidget;
class DownloadTopAreaWidget;
class DownloadRightAreaWidget;
class DownloadLeftAreaWidget;
class DownloadApplicationModule;

namespace Ui {
class DownloadApplication;
}

/*! @brief The class of the app main widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadApplication : public TTKAbstractMoveResizeWidget
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadApplication(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadApplication();

    /*!
     * Get class object instance.
     */
    static DownloadApplication *instance();

public Q_SLOTS:
    /*!
     * Apply settings parameters.
     */
    void applyParameter();
    /*!
     * Show maximized window.
     */
    void showMaximizedWindow();
    /*!
     * Application window close.
     */
    void quitWindow();
    /*!
     * Create right menu.
     */
    void createRightMenu();

private:
    /*!
     * Override the widget event.
     */
    virtual void resizeEvent(QResizeEvent *event) override final;
    virtual void closeEvent(QCloseEvent *event) override final;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override final;

    /*!
     * Read XML config from text.
     */
    void readSystemConfigFromFile();
    /*!
     * Write XML config to text.
     */
    void writeSystemConfigToFile();

    Ui::DownloadApplication *m_ui;

    DownloadBottomAreaWidget *m_bottomAreaWidget;
    DownloadTopAreaWidget *m_topAreaWidget;
    DownloadRightAreaWidget *m_rightAreaWidget;
    DownloadLeftAreaWidget *m_leftAreaWidget;
    DownloadApplicationModule *m_applicationModule;

    static DownloadApplication *m_instance;
};

#endif // DOWNLOADAPPLICATION_H
