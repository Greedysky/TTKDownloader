#ifndef DOWNLOADSETTINGWIDGET_H
#define DOWNLOADSETTINGWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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
 ================================================= */

#include "downloadobject.h"
#include "downloadabstractmovedialog.h"
#include "downloadabstracttablewidget.h"

namespace Ui {
class DownloadSettingWidget;
}

/*! @brief The class of the function tool item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_WIDGET_EXPORT DownloadFunctionItem
{
    DownloadFunctionItem() { }
    DownloadFunctionItem(const QString &icon, const QString &name)
    {
        m_icon = icon;
        m_name = name;
    }

    QString m_icon;
    QString m_name;
}DownloadFunctionItem;
TTK_DECLARE_LISTS(DownloadFunctionItem)

/*! @brief The class of the list table widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadFunctionTableWidget : public DownloadAbstractTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadFunctionTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadFunctionTableWidget(QWidget *parent = nullptr);

    /*!
     * Add table list items by index and icons and paths.
     */
    void addFunctionItems(int index, const DownloadFunctionItems &items);

Q_SIGNALS:
    /*!
     * Current list index changed.
     */
    void currentIndexChanged(int index);

public Q_SLOTS:
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;

protected:
    /*!
     * Override the widget event.
     */
    virtual void leaveEvent(QEvent *event) override;

    int m_listIndex;
};


/*! @brief The class of the setting parameters widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadSettingWidget : public DownloadAbstractMoveDialog
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadSettingWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSettingWidget(QWidget *parent = nullptr);

    virtual ~DownloadSettingWidget();

    /*!
     * Init controller parameter to widget.
     */
    void initControllerParameter();

Q_SIGNALS:
    /*!
     * Parameters setting changed emit.
     */
    void parameterSettingChanged();

public Q_SLOTS:
    /*!
     * Clear all function tables selection.
     */
    void clearFunctionTableSelection();
    /*!
     * Set select download dir.
     */
    void downloadDirSelected();
    /*!
     * Set enable or disable download speed limit.
     */
    void downloadGroupSpeedLimit(int index);
    /*!
     * Save the change results.
     */
    void commitTheResults();
    /*!
     * Override exec function.
     */
    virtual int exec();

protected:
    /*!
     * Select function table index.
     */
    void selectFunctionTableIndex(int row, int col);
    /*!
     * Init normal setting stack widget.
     */
    void initNormalSettingWidget();
    /*!
     * Init download setting stack widget.
     */
    void initDownloadSettingWidget();
    /*!
     * Init download setting stack widget.
     */
    void initSkinSettingWidget();

    Ui::DownloadSettingWidget *m_ui;

};

#endif // DOWNLOADETTINGWIDGET_H
