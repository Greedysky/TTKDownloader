#ifndef DOWNLOADLEFTAREAWIDGET_H
#define DOWNLOADLEFTAREAWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "downloadglobaldefine.h"

namespace Ui {
    class DownloadApplication;
}

/*! @brief The class of the app left area widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_GUI_EXPORT DownloadLeftAreaWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadLeftAreaWidget(QWidget *parent = 0);

    ~DownloadLeftAreaWidget();
    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Get class object instance.
     */
    static DownloadLeftAreaWidget *instance();
    /*!
     * Set up app ui.
     */
    void setupUi(Ui::DownloadApplication* ui);

public Q_SLOTS:
    /*!
     * Show setting widget.
     */
    void showSettingWidget();

protected:

    Ui::DownloadApplication *m_ui;

    static DownloadLeftAreaWidget *m_instance;
};

#endif // DOWNLOADLEFTAREAWIDGET_H
