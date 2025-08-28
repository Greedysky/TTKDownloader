#ifndef DOWNLOADFUNCTIONLISTWIDGET_H
#define DOWNLOADFUNCTIONLISTWIDGET_H

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
#include "ttkmoduleexport.h"

/*! @brief The class of the function list widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadFunctionItemWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadFunctionItemWidget(QWidget *parent = nullptr);

    /*!
     * Set label text.
     */
    void setLabelText(const QString &text) noexcept;
    /*!
     * Set label icon.
     */
    void setLabelIcon(const QString &iconf, const QString &iconb) noexcept;
    /*!
     * Set selected state.
     */
    void setSelectedMode(bool select);
    /*!
     * Resize mode.
     */
    void resizeMode(bool mode);

Q_SIGNALS:
    /*!
     * Selected state changed.
     */
    void selectedChanged(DownloadFunctionItemWidget *item);

private:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override final;
    virtual void enterEvent(QtEnterEvent *event) override final;
    virtual void leaveEvent(QEvent *event) override final;
    virtual void paintEvent(QPaintEvent *event) override final;

    QString m_text, m_iconf, m_iconb;
    bool m_enterIn, m_selectedOn, m_resizeMode;

};


/*! @brief The class of the function list widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadFunctionListWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadFunctionListWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadFunctionListWidget();

    /*!
     * Resize mode.
     */
    void resizeMode(bool mode);

Q_SIGNALS:
    /*!
     * Current selected index changed.
     */
    void currentIndexChanged(int index);

public Q_SLOTS:
    /*!
     * Selected state changed.
     */
    void selectedChanged(DownloadFunctionItemWidget *item);

private:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override final;

    QList<DownloadFunctionItemWidget*> m_items;

};

#endif // DOWNLOADFUNCTIONLISTWIDGET_H
