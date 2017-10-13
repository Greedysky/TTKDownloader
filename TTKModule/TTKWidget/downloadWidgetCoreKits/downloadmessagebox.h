#ifndef DOWNLOADMESSAGEBOX_H
#define DOWNLOADMESSAGEBOX_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2017 Greedysky Studio

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

#include "downloadabstractmovedialog.h"

namespace Ui {
class DownloadMessageBox;
}

/*! @brief The class of the messagebox widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadMessageBox : public DownloadAbstractMoveDialog
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadMessageBox(QWidget *parent = 0);
    /*!
     * Object contsructor by context text.
     */
    explicit DownloadMessageBox(const QString &text, QWidget *parent = 0);
    /*!
     * Object contsructor by context text and title.
     */
    DownloadMessageBox(const QString &title, const QString &text,
                    QWidget *parent = 0);

    virtual ~DownloadMessageBox();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Set box title.
     */
    void setTitle(const QString &text) const;
    /*!
     * Get box title.
     */
    QString title() const;
    /*!
     * Set context text.
     */
    void setText(const QString &text) const;
    /*!
     * Get context text.
     */
    QString text() const;

public Q_SLOTS:
    /*!
     * Confirm or cancal button clicked, set the state.
     */
    void buttonClicked(int index);
    /*!
     * Override exec function.
     */
    virtual int exec();
    /*!
     * Override show function.
     */
    void show();

protected:
    Ui::DownloadMessageBox *m_ui;
    int m_status;

};

#endif // DOWNLOADMESSAGEBOX_H
