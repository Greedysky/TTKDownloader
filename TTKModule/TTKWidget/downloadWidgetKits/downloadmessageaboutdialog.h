#ifndef DOWNLOADMESSAGEABOUTDIALOG_H
#define DOWNLOADMESSAGEABOUTDIALOG_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractmovedialog.h"

namespace Ui {
    class DownloadMessageAboutDialog;
}
/*! @brief The class of the about application info dialog.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadMessageAboutDialog : public DownloadAbstractMoveDialog
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadMessageAboutDialog(QWidget *parent = 0);

    virtual ~DownloadMessageAboutDialog();

    /*!
     * Get class object name.
     */
    static QString getClassName();

public Q_SLOTS:
    /*!
     * Override exec function.
     */
    virtual int exec();

protected:
    Ui::DownloadMessageAboutDialog *m_ui;

};

#endif // DOWNLOADMESSAGEABOUTDIALOG_H
