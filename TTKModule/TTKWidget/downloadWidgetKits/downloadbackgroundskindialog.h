#ifndef DOWNLOADBACKGROUNDSKINDIALOG_H
#define DOWNLOADBACKGROUNDSKINDIALOG_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractmovedialog.h"

namespace Ui {
class DownloadBackgroundSkinDialog;
}

class DownloadBackgroundListWidget;
class DownloadBackgroundRemoteWidget;

/*! @brief The class of the local background widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadBackgroundSkinDialog : public DownloadAbstractMoveDialog
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBackgroundSkinDialog(QWidget *parent = 0);

    virtual ~DownloadBackgroundSkinDialog();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Set artist background picture by name.
     */
    static QPixmap setMBackground(QString &name);
    /*!
     * Theme valid check.
     */
    static bool themeValidCheck(QString &name, QString &path);
    /*!
     * Copy art file to local themes dir path.
     */
    static QString cpoyArtFileToLocal(const QString &path);
    /*!
     * Update art file theme.
     */
    void updateArtFileTheme(const QString &theme);

    /*!
     * Select current item by name\alpha\listAlpha when the widget show.
     */
    void setCurrentBgTheme(const QString &theme, int alpha);

    /*!
     * Set skin transparent tool text.
     */
    void setSkinTransToolText(int value);

Q_SIGNALS:
    /*!
     * Update app bg when user change the current bg emit.
     */
    void currentTextChanged(const QString &text);

public Q_SLOTS:
    /*!
     * Change index to palette dialog.
     */
    void showPaletteDialog();
    /*!
     * Change index to palette dialog.
     */
    void showPaletteDialog(const QString &path);
    /*!
     * Change index to custom skin dialog.
     */
    void showCustomSkinDialog();
    /*!
     * Background list widget changed.
     */
    void backgroundListWidgetChanged(int index);
    /*!
     * Background list widget item has clicked.
     */
    void backgroundListWidgetItemClicked(const QString &name);
    /*!
     * My background list widget item has clicked.
     */
    void myBackgroundListWidgetItemClicked(const QString &name);
    /*!
     * Remote background list widget item has clicked.
     */
    void remoteBackgroundListWidgetItemClicked(const QString &name);
    /*!
     * Override exec function.
     */
    virtual int exec();

protected:
    /*!
     * Background list widget item has clicked changed.
     */
    void listWidgetItemClicked(DownloadBackgroundListWidget *item, const QString &name);
    /*!
     * Add all theme into list.
     */
    void addThemeListWidgetItem();
    /*!
     * Copy custom file to local themes dir path.
     */
    void cpoyFileFromLocal(const QString &path);
    /*!
     * Copy custom file index.
     */
    static int cpoyFileToLocalIndex();
    /*!
     * Copy custom file .
     */
    static int cpoyFileToLocal(const QString &path);

    int m_myThemeIndex;
    Ui::DownloadBackgroundSkinDialog *m_ui;
    DownloadBackgroundListWidget *m_backgroundList, *m_myBackgroundList;
    DownloadBackgroundRemoteWidget *m_remoteBackgroundList;

};

#endif // DOWNLOADBACKGROUNDSKINDIALOG_H
