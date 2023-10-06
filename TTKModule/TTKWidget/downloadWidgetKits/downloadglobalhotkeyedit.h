#ifndef DOWNLOADGLOBALHOTKEYEDIT_H
#define DOWNLOADGLOBALHOTKEYEDIT_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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

#include <QLineEdit>
#include "ttkmoduleexport.h"

/*! @brief The class of the global hotKey lineEdit.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadGlobalHotKeyEdit : public QLineEdit
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadGlobalHotKeyEdit)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadGlobalHotKeyEdit(QWidget *parent = nullptr);

    /*!
     * Set hotKey enable state.
     */
    void setHotKeyEnabled(bool state);

private:
    /*!
     * Override the widget event.
     */
    virtual void keyPressEvent(QKeyEvent *event) override final;

};

#endif // DOWNLOADGLOBALHOTKEYEDIT_H
