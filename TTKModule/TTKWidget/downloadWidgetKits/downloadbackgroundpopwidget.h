#ifndef DOWNLOADBACKGROUNDPOPWIDGET_H
#define DOWNLOADBACKGROUNDPOPWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadtoolmenuwidget.h"

class DownloadClickedSlider;

/*! @brief The class of the background popup widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadBackgroundPopWidget : public DownloadToolMenuWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBackgroundPopWidget(QWidget *parent = 0);

    virtual ~DownloadBackgroundPopWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

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
    void initWidget();

    DownloadClickedSlider *m_slider;

};

#endif // DOWNLOADBACKGROUNDPOPWIDGET_H
