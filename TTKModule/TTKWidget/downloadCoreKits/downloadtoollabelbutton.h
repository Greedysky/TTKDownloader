#ifndef DOWNLOADTOOLLABELBUTTON_H
#define DOWNLOADTOOLLABELBUTTON_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2026 Greedysky Studio

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

#include <QToolButton>
#include "ttkmoduleexport.h"

class QLabel;

/*! @brief The class of the label tool button.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadToolLabelButton : public QToolButton
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadToolLabelButton(QWidget *parent = nullptr);

    /*!
     * Set label text.
     */
    void setLabelText(const QString &text);
    /*!
     * Set label icon.
     */
    void setLabelIcon(const QString &icon);

Q_SIGNALS:
    /*!
     * Mouse clicked.
     */
    void mouseClicked();

private:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override final;
    virtual void enterEvent(QtEnterEvent *event) override final;
    virtual void leaveEvent(QEvent *event) override final;
    virtual void paintEvent(QPaintEvent *event) override final;

    bool m_enterIn;
    QString m_text, m_icon;

};

/*! @brief The class of the speed label tool button.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadSpeedToolLabelButton : public QToolButton
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadSpeedToolLabelButton(QWidget *parent = nullptr);

    /*!
     * Set label text.
     */
    void setLabelText(const QString &up, const QString &down);

private:
    /*!
     * Override the widget event.
     */
    virtual void enterEvent(QtEnterEvent *event) override final;
    virtual void leaveEvent(QEvent *event) override final;
    virtual void paintEvent(QPaintEvent *event) override final;

    QString m_textUp, m_textDown;
    bool m_enterIn;

};


#endif // DOWNLOADTOOLLABELBUTTON_H
