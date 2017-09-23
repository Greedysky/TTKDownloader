#ifndef DOWNLOADTOOLLABELBUTTON_H
#define DOWNLOADTOOLLABELBUTTON_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QToolButton>
#include "downloadglobaldefine.h"

class QLabel;

/*! @brief The class of the label tool button.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadToolLabelButton : public QToolButton
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadToolLabelButton(QWidget *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Set label text.
     */
    void setLabelText(const QString &text);
    /*!
     * Set label icon.
     */
    void setLabelIcon(const QString &icon);

protected:
    /*!
     * Override the widget event.
     */
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    QString m_text, m_icon;
    bool m_enterIn;

};

/*! @brief The class of the speed label tool button.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadSpeedToolLabelButton : public QToolButton
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSpeedToolLabelButton(QWidget *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Set label text.
     */
    void setLabelText(const QString &up, const QString &down);

protected:
    /*!
     * Override the widget event.
     */
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    QString m_textUp, m_textDown;
    bool m_enterIn;

};


#endif // DOWNLOADTOOLLABELBUTTON_H
