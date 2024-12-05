#ifndef DOWNLOADBACKGROUNDSKINDIALOG_H
#define DOWNLOADBACKGROUNDSKINDIALOG_H

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

#include "downloadabstractmovedialog.h"

namespace Ui {
class DownloadBackgroundSkinDialog;
}

class DownloadBackgroundListWidget;
class DownloadBackgroundOnlineWidget;

/*! @brief The class of the local background widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBackgroundSkinDialog : public DownloadAbstractMoveDialog
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBackgroundSkinDialog)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadBackgroundSkinDialog(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadBackgroundSkinDialog();

    /*!
     * Set artist background picture by name.
     */
    static QPixmap setBackgroundUrl(QString &name);
    /*!
     * Theme is valid check.
     */
    static bool isValid(QString &name, QString &path);

    /*!
     * Select current item by name and background transparent when the widget show.
     */
    void setCurrentBackgroundTheme(const QString &theme, int background);

    /*!
     * Set skin transparent tool text.
     */
    void setSkinTransToolText(int value);

Q_SIGNALS:
    /*!
     * Update app bg when user change the current bg.
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
     * Classical list widget item has clicked.
     */
    void classicalListWidgetItemClicked(int type, const QString &name);
    /*!
     * Remote background list widget item has clicked.
     */
    void remoteListWidgetItemClicked(int type, const QString &name);

private:
    /*!
     * Background list widget item has clicked changed.
     */
    void listWidgetItemClicked(DownloadBackgroundListWidget *item, const QString &name);
    /*!
     * Add all theme into list.
     */
    void addThemeListWidgetItem();
    /*!
     * Add all theme into list.
     */
    void addThemeListWidgetItem(DownloadBackgroundListWidget *item, const QString &dir, bool state);
    /*!
     * Copy custom file to local themes dir path.
     */
    void cpoyFileFromLocal(const QString &path);

    /*!
     * Find all theme in local directory.
     */
    static void findThemeListByPath(const QString &dir, TTKIntList &data);
    /*!
     * Copy custom file index.
     */
    static int cpoyFileToLocalIndex();
    /*!
     * Copy custom file .
     */
    static int cpoyFileToLocal(const QString &path);

    Ui::DownloadBackgroundSkinDialog *m_ui;

    int m_stackThemeIndex;
    DownloadBackgroundListWidget *m_cacheBackgroundList;
    DownloadBackgroundListWidget *m_stackBackgroundList;
    DownloadBackgroundOnlineWidget *m_onlineBackgroundList;

};

#endif // DOWNLOADBACKGROUNDSKINDIALOG_H
