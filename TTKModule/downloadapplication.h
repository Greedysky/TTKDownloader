#ifndef DOWNLOADAPPLICATION_H
#define DOWNLOADAPPLICATION_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractmoveresizewidget.h"

class DownloadBottomAreaWidget;
class DownloadTopAreaWidget;
class DownloadRightAreaWidget;
class DownloadLeftAreaWidget;
class DownloadApplicationObject;

namespace Ui {
class DownloadApplication;
}

/*! @brief The class of the app main widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_GUI_EXPORT DownloadApplication : public DownloadAbstractMoveResizeWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadApplication(QWidget *parent = 0);

    virtual ~DownloadApplication();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Get class object instance.
     */
    static DownloadApplication *instance();

public Q_SLOTS:
    /*!
     * Get settings parameters.
     */
    void getParameterSetting();
    /*!
     * Show maximized window.
     */
    void showMaximizedWindow();
    /*!
     * Application window close.
     */
    void quitWindowClose();
    /*!
     * Create right menu.
     */
    void appCreateRightMenu();

private:
    /*!
     * Override the widget event.
     */
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    /*!
     * Read XML config from text.
     */
    void readXMLConfigFromText();
    /*!
     * Write XML config to text.
     */
    void writeXMLConfigToText();

    Ui::DownloadApplication *m_ui;

    DownloadBottomAreaWidget *m_bottomAreaWidget;
    DownloadTopAreaWidget *m_topAreaWidget;
    DownloadRightAreaWidget *m_rightAreaWidget;
    DownloadLeftAreaWidget *m_leftAreaWidget;
    DownloadApplicationObject *m_applicationObject;

    static DownloadApplication *m_instance;
};

#endif // DOWNLOADAPPLICATION_H
