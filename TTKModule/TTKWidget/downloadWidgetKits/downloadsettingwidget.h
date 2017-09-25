#ifndef DOWNLOADSETTINGWIDGET_H
#define DOWNLOADSETTINGWIDGET_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

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
DOWNLOAD_DECLARE_LISTS(DownloadFunctionItem)

/*! @brief The class of the list table widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadFunctionTableWidget : public DownloadAbstractTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadFunctionTableWidget(QWidget *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();
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
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSettingWidget(QWidget *parent = 0);

    virtual ~DownloadSettingWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

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

    Ui::DownloadSettingWidget *m_ui;

};

#endif // DOWNLOADETTINGWIDGET_H
