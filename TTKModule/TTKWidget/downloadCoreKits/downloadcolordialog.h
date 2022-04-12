#ifndef DOWNLOADCOLORDIALOG_H
#define DOWNLOADCOLORDIALOG_H

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

#include "downloadabstractmovedialog.h"

/*! @brief The class of the color hl palette.
 * @author ToDo <278488569@qq.com>
 */
class TTK_MODULE_EXPORT DownloadHlPalette : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadHlPalette)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadHlPalette(QWidget *parent = nullptr);

    /*!
     * Get color.
     */
    QColor color() const;
    /*!
     * Init parameter.
     */
    void initialize();

Q_SIGNALS:
    /*!
     * Current color has changed.
     */
    void colorChanged(const QColor &color);

public Q_SLOTS:
    /*!
     * Set current color saturation.
     */
    void setSaturation(double dblsaturation);

protected:
    /*!
     * Override the widget event.
     */
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    /*!
     * Calculate current color.
     */
    void calculateColor();

    QPoint m_ptVernierPos;
    QPointF m_ptfVernierPercentPos;
    QColor m_color;
    double m_dblSaturation;

};


/*! @brief The class of the color hl saturation palette.
 * @author ToDo <278488569@qq.com>
 */
class TTK_MODULE_EXPORT DownloadHlSaturationPalette : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadHlSaturationPalette)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadHlSaturationPalette(QWidget *parent = nullptr);

    /*!
     * Get saturation.
     */
    double saturation() const;

Q_SIGNALS:
    /*!
     * Current saturation has changed.
     */
    void saturationChanged(double dblSaturation);

public Q_SLOTS:
    /*!
     * Set current color.
     */
    void setBaseColor(const QColor &color);

protected:
    /*!
     * Override the widget event.
     */
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    /*!
     * Calculate current saturation.
     */
    void calculateSuration();

    QColor m_color;
    double m_dblVernierX, m_dblVernierPercentX, m_dblSaturation;

};


namespace Ui {
class DownloadColorDialog;
}

/*! @brief The class of the get color table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadColorDialog : public DownloadAbstractMoveDialog
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadColorDialog)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadColorDialog(QWidget *parent = nullptr);
    ~DownloadColorDialog();

    /*!
     * Get color static function.
     */
    static QColor popup(QWidget *parent = nullptr);
    /*!
     * Get color.
     */
    QColor color() const;

public Q_SLOTS:
    /*!
     * Confirm or cancal button clicked, set the state.
     */
    void buttonClicked(int index);
    /*!
     * Current color has changed.
     */
    void colorChanged(const QColor &color);
    /*!
     * Override exec function.
     */
    virtual int exec();

protected:
    Ui::DownloadColorDialog *m_ui;

    int m_status;
    QColor m_color;

};

#endif // DOWNLOADCOLORDIALOG_H
