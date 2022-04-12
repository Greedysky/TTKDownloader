#ifndef DOWNLOADBACKGROUNDPOPWIDGET_H
#define DOWNLOADBACKGROUNDPOPWIDGET_H

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

#include "downloadtoolmenuwidget.h"

class DownloadClickedSlider;

/*! @brief The class of the background popup widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBackgroundPopWidget : public DownloadToolMenuWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBackgroundPopWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBackgroundPopWidget(QWidget *parent = nullptr);
    ~DownloadBackgroundPopWidget();

    /*!
     * Set slider value.
     */
    void setValue(int value);
    /*!
     * Get slider value.
     */
    int value() const;

Q_SIGNALS:
    /*!
     * Current play transparent changed.
     */
    void valueChanged(int value);
    /*!
     * Current slider state changed.
     */
    void sliderStateChanged(bool state);

private Q_SLOTS:
    /*!
     * Current slider pressed changed.
     */
    void sliderPressed();
    /*!
     * Current slider released changed.
     */
    void sliderReleased();

protected:
    /*!
     * Create all widget in layout.
     */
    void initialize();

    DownloadClickedSlider *m_slider;

};

#endif // DOWNLOADBACKGROUNDPOPWIDGET_H
