#ifndef DOWNLOADNEWFILEDIALOG_H
#define DOWNLOADNEWFILEDIALOG_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractmovedialog.h"

namespace Ui {
class DownloadNewFileDialog;
}

/*! @brief The class of the download new filed dialog.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadNewFileDialog : public DownloadAbstractMoveDialog
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadNewFileDialog(QWidget *parent = 0);

    ~DownloadNewFileDialog();

    /*!
     * Get class object name.
     */
    static QString getClassName();

Q_SIGNALS:
    /*!
     * Downlaod url changed.
     */
    void setDownloadPath(const QStringList &paths);

public Q_SLOTS:
    /*!
     * Override exec function.
     */
    virtual int exec();
    /*!
     * Congorm button clicked.
     */
    void confirmButtonPressed();

protected:
    Ui::DownloadNewFileDialog *m_ui;

};

#endif // DOWNLOADNEWFILEDIALOG_H
