#ifndef DOWNLOADTRANSITIONANIMATIONLABEL_H
#define DOWNLOADTRANSITIONANIMATIONLABEL_H

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

#include <QLabel>
#include "ttkmoduleexport.h"

class QPropertyAnimation;

/*! @brief The class of the label transition animation.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadTransitionAnimationLabel : public QLabel
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadTransitionAnimationLabel)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadTransitionAnimationLabel(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadTransitionAnimationLabel();

    /*!
     * Set animation to start.
     */
    inline void setAnimation(bool enable) noexcept { m_animationEnabled = enable; }
    /*!
     * Get animation state.
     */
    inline bool animation() const noexcept { return m_animationEnabled; }

    /*!
     * Get render pixmap image.
     */
    const QPixmap& renderPixmap() const;

    /*!
     * Start renderer pixmap animation.
     */
    void start();
    /*!
     * Stop renderer pixmap animation.
     */
    void stop();

    /*!
     * Get animation is in run state.
     */
    bool isRunning() const;

public Q_SLOTS:
    /*!
     * Override the setPixmap function.
     */
    void setPixmap(const QPixmap &pix);

private Q_SLOTS:
    /*!
     * Animation value changed.
     */
    void valueChanged(const QVariant &value);
    /*!
     * Animation finished.
     */
    void animationFinished();

private:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override final;

    bool m_isAnimating;
    int m_currentValue;
    bool m_animationEnabled;
    QPixmap m_renderPixmap;
    QPixmap m_currentPixmap, m_previousPixmap;
    QPropertyAnimation *m_animation;

};

#endif // DOWNLOADTRANSITIONANIMATIONLABEL_H
