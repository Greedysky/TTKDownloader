#ifndef DOWNLOADLEFTAREAWIDGET_H
#define DOWNLOADLEFTAREAWIDGET_H

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

namespace Ui {
    class DownloadApplication;
}

/*! @brief The class of the app left area widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadLeftAreaWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadLeftAreaWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadLeftAreaWidget(QWidget *parent = nullptr);
    ~DownloadLeftAreaWidget();

    /*!
     * Get class object instance.
     */
    static DownloadLeftAreaWidget *instance();
    /*!
     * Set up app ui.
     */
    void setupUi(Ui::DownloadApplication* ui);

public Q_SLOTS:
    /*!
     * Current selected index changed.
     */
    void funcitonIndexChanged(int index);
    /*!
     * Show setting widget.
     */
    void showSettingWidget();

private:

    Ui::DownloadApplication *m_ui;

    static DownloadLeftAreaWidget *m_instance;

};

#endif // DOWNLOADLEFTAREAWIDGET_H
