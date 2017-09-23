#ifndef DOWNLOADFUNCTIONLISTWIDGET_H
#define DOWNLOADFUNCTIONLISTWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "downloadglobaldefine.h"

/*! @brief The class of the function list widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadFunctionItemWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadFunctionItemWidget(QWidget *parent = 0);

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
    void setLabelIcon(const QString &iconf, const QString &iconb);
    /*!
     * Set selected state.
     */
    void setSelectedMode(bool select);

Q_SIGNALS:
    /*!
     * Selected state changed.
     */
    void selectedChanged(DownloadFunctionItemWidget *item);

protected:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    QString m_text, m_iconf, m_iconb;
    bool m_enterIn, m_selectedOn;
};


/*! @brief The class of the function list widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadFunctionListWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadFunctionListWidget(QWidget *parent = 0);

    ~DownloadFunctionListWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

public Q_SLOTS:
    /*!
     * Selected state changed.
     */
    void selectedChanged(DownloadFunctionItemWidget *item);

protected:
    QList<DownloadFunctionItemWidget*> m_items;

};

#endif // DOWNLOADFUNCTIONLISTWIDGET_H
