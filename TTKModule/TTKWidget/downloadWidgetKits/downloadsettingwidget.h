#ifndef DOWNLOADSETTINGWIDGET_H
#define DOWNLOADSETTINGWIDGET_H

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

#include "downloadobject.h"
#include "downloadabstractmovedialog.h"
#include "downloadabstracttablewidget.h"

class DownloadGlobalHotKeyEdit;

namespace Ui {
class DownloadSettingWidget;
}

/*! @brief The class of the function tool item.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadFunctionItem
{
    QString m_icon;
    QString m_name;

    DownloadFunctionItem(const QString &icon, const QString &name) noexcept
        : m_icon(icon),
          m_name(name)
    {

    }
};
TTK_DECLARE_LIST(DownloadFunctionItem);

/*! @brief The class of the list table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadFunctionTableWidget : public DownloadAbstractTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadFunctionTableWidget)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadFunctionTableWidget(QWidget *parent = nullptr);

    /*!
     * Add table list items by index and icons and paths.
     */
    void addCellItems(int index, const DownloadFunctionItemList &items);

Q_SIGNALS:
    /*!
     * Current list index changed.
     */
    void currentIndexChanged(int index);

public Q_SLOTS:
    /*!
     * Table widget item cell click.
     */
    virtual void itemCellClicked(int row, int column) override final;

private:
    int m_listIndex;

};


/*! @brief The class of the setting parameters widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadSettingWidget : public DownloadAbstractMoveDialog
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadSettingWidget)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadSettingWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadSettingWidget();

    /*!
     * Init controller parameter to widget.
     */
    void initialize();

Q_SIGNALS:
    /*!
     * Parameters setting changed.
     */
    void parameterSettingChanged();

public Q_SLOTS:
    /*!
     * Clear all function tables selection.
     */
    void clearFunctionTableSelection();
    /*!
     * Set global hotkey box changed.
     */
    void globalHotkeyBoxChanged(bool state);
    /*!
     * Set select download dir.
     */
    void downloadDirChanged();
    /*!
     * Set enable or disable download speed limit.
     */
    void downloadGroupSpeedLimit(int index);
    /*!
     * Save the parameter setting results.
     */
    void saveParameterSettings();

private:
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

    QVector<DownloadGlobalHotKeyEdit*> m_hotKeyEdits;

};

#endif // DOWNLOADETTINGWIDGET_H
