#ifndef DOWNLOADFUNTIONANIMATIONWIDGET_H
#define DOWNLOADFUNTIONANIMATIONWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2024 Greedysky Studio

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

class QButtonGroup;
class QPropertyAnimation;

/*! @brief The class of the animation base widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadAbstractAnimationWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadAbstractAnimationWidget)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadAbstractAnimationWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadAbstractAnimationWidget();

Q_SIGNALS:
    /*!
     * Switch to selected item style.
     */
    void buttonClicked(int index);

public Q_SLOTS:
    /*!
     * Switch to selected item style.
     */
    virtual void switchToSelectedItemStyle(int index);
    /*!
     * Animation state changed.
     */
    void animationChanged(const QVariant &value);
    /*!
     * Animation finished.
     */
    void finished();

protected:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override;

    QPixmap m_pix;
    int m_curIndex, m_preIndex, m_x;
    float m_perWidth, m_totalWidth;
    bool m_isAnimation, m_showState, m_showLine;

    QPropertyAnimation *m_animation;
    QWidgetList m_container;
    QButtonGroup *m_buttonGroup;

};


/*! @brief The class of the function skin animation widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadSkinAnimationWidget : public DownloadAbstractAnimationWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadSkinAnimationWidget)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadSkinAnimationWidget(QWidget *parent = nullptr);

public Q_SLOTS:
    /*!
     * Switch to selected item style.
     */
    virtual void switchToSelectedItemStyle(int index) override final;

private:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override final;

};

#endif // DOWNLOADFUNTIONANIMATIONWIDGET_H
