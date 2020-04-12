#ifndef DOWNLOADBACKGROUNDLISTWIDGET_H
#define DOWNLOADBACKGROUNDLISTWIDGET_H

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

#include <QLabel>
#include <QGridLayout>
#include "downloaduiobject.h"
#include "downloadbackgroundconfigmanager.h"

#define CURRENT_ITEMS_COUNT         47

/*! @brief The class of the background list item.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadBackgroundListItem : public QLabel
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBackgroundListItem(QWidget *parent = nullptr);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Set item file name.
     */
    inline void setFileName(const QString &name) { m_name = name; }
    /*!
     * Get item file name.
     */
    inline QString getFileName() const { return m_name; }
    /*!
     * Set item file name.
     */
    inline void setFilePath(const QString &path) { m_path = path; }
    /*!
     * Get item file name.
     */
    inline QString getFilePath() const { return m_path; }

    /*!
     * Update pix image.
     */
    void updatePixImage();
    /*!
     * Update pix image.
     */
    void updatePixImage(const DownloadBackgroundImage &image);
    /*!
     * Current item contains or not.
     */
    bool contains(const DownloadSkinConfigItem &item) const;

    /*!
     * Select the current item.
     */
    void setSelect(bool s);
    /*!
     * Get current selected item state.
     */
    inline bool isSelect() const { return m_isSelected; }

    /*!
     * Select the current item enable or not.
     */
    void setSelectEnable(bool s);
    /*!
     * Get current selected item state.
     */
    inline bool isSelectEnable() const { return m_selectedMask; }

    /*!
     * Close option set the current item.
     */
    void setCloseEnable(bool s);
    /*!
     * Get close option set the current item.
     */
    inline bool isCloseEnable() const { return m_closeSet; }


Q_SIGNALS:
    /*!
     * Current item close clicked.
     */
    void closeClicked(DownloadBackgroundListItem *item);
    /*!
     * Current item clicked.
     */
    void itemClicked(DownloadBackgroundListItem *item);

protected:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    bool m_printMask, m_isSelected, m_selectedMask;
    bool m_closeMask, m_closeSet;
    QString m_name, m_path;
    DownloadSkinConfigItem m_imageInfo;

};


/*! @brief The class of the background list widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadBackgroundListWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBackgroundListWidget(QWidget *parent = nullptr);

    ~DownloadBackgroundListWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Select current item by name when the widget show.
     */
    void setCurrentItemName(const QString &name);

    /*!
     * Clear select state.
     */
    void clearSelectState();
    /*!
     * Clear All Items.
     */
    void clearAllItems();

    /*!
     * Create item by name and path.
     */
    void createItem(const QString &name, const QString &path, bool state);
    /*!
     * Create item by icon.
     */
    void createItem(const QString &icon, bool state);
    /*!
     * Update item by backgroud image.
     */
    void updateItem(const DownloadBackgroundImage &image, const QString &path);

    /*!
     * Current item contains or not.
     */
    bool contains(const QString &name) const;
    /*!
     * Current item contains or not.
     */
    bool contains(const DownloadBackgroundImage &image) const;

    /*!
     * Current item index at container.
     */
    int find(DownloadBackgroundListItem *item) const;
    /*!
     * Find item by name.
     */
    DownloadBackgroundListItem* find(const QString &name) const;
    /*!
     * Find item by image.
     */
    DownloadBackgroundListItem* find(const DownloadBackgroundImage &image) const;

    /*!
     * Update lasted item state.
     */
    void updateLastedItem();

    /*!
     * Item count.
     */
    inline int count() const { return m_items.count(); }

Q_SIGNALS:
    /*!
     * Current item clicked.
     */
    void itemClicked(const QString &name);

private Q_SLOTS:
    /*!
     * Current item close clicked.
     */
    void itemCloseClicked(DownloadBackgroundListItem *item);
    /*!
     * Current item has clicked.
     */
    void itemHasClicked(DownloadBackgroundListItem *item);

protected:
    QGridLayout *m_layout;
    DownloadBackgroundListItem *m_currentItem;
    QList<DownloadBackgroundListItem*> m_items;

};

#endif // DOWNLOADBACKGROUNDLISTWIDGET_H
