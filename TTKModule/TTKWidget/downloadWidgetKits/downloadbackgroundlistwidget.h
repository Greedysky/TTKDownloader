#ifndef DOWNLOADBACKGROUNDLISTWIDGET_H
#define DOWNLOADBACKGROUNDLISTWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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

#include <QLabel>
#include <QGridLayout>
#include "downloaduiobject.h"
#include "downloadbackgroundconfigmanager.h"

/*! @brief The class of the background list item.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBackgroundListItem : public QLabel
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBackgroundListItem)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadBackgroundListItem(QWidget *parent = nullptr);

    /*!
     * Set item file name.
     */
    inline void setFileName(const QString &name) { m_name = name; }
    /*!
     * Get item file name.
     */
    inline QString fileName() const { return m_name; }
    /*!
     * Set item file name.
     */
    inline void setFilePath(const QString &path) { m_path = path; }
    /*!
     * Get item file name.
     */
    inline QString filePath() const { return m_path; }

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
    void setSelected(bool s);
    /*!
     * Get current selected item state.
     */
    inline bool isSelected() const { return m_isSelected; }

    /*!
     * Select the current item enable or not.
     */
    void setSelectEnabled(bool s);
    /*!
     * Get current selected item state.
     */
    inline bool isSelectEnabled() const { return m_selectedEnabled; }

    /*!
     * Close option set the current item.
     */
    void setCloseEnabled(bool s);
    /*!
     * Get close option set the current item.
     */
    inline bool isCloseEnabled() const { return m_closeEnabled; }

Q_SIGNALS:
    /*!
     * Current item close clicked.
     */
    void closeClicked(DownloadBackgroundListItem *item);
    /*!
     * Current item clicked.
     */
    void itemClicked(DownloadBackgroundListItem *item);

private:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override final;
    virtual void leaveEvent(QEvent *event) override final;
    virtual void enterEvent(QtEnterEvent *event) override final;
    virtual void paintEvent(QPaintEvent *event) override final;

    bool m_isSelected, m_printMask;
    bool m_selectedEnabled, m_closeEnabled;
    QString m_name, m_path;
    DownloadSkinConfigItem m_imageInfo;

};


/*! @brief The class of the background list widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBackgroundListWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBackgroundListWidget)
public:
    enum Module
    {
        CachedModule,
        StackedModule,
        OnlineModule
    };

    /*!
     * Object constructor.
     */
    explicit DownloadBackgroundListWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadBackgroundListWidget();

    /*!
     * Select current item by name when the widget show.
     */
    void setCurrentItemName(const QString &name);

    /*!
     * Set background list rtpe.
     */
    inline void setType(Module type) { m_type = type; }
    /*!
     * Get background list rtpe.
     */
    inline Module type() const { return m_type; }

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
    void addCellItem(const QString &name, const QString &path, bool state);
    /*!
     * Create item by icon.
     */
    void addCellItem(const QString &icon, bool state);
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
    void itemClicked(int type, const QString &name);

private Q_SLOTS:
    /*!
     * Current item close clicked.
     */
    void itemCloseClicked(DownloadBackgroundListItem *item);
    /*!
     * Current item has clicked.
     */
    void currentItemClicked(DownloadBackgroundListItem *item);

private:
    Module m_type;
    QGridLayout *m_gridLayout;
    DownloadBackgroundListItem *m_currentItem;
    QList<DownloadBackgroundListItem*> m_items;

};

#endif // DOWNLOADBACKGROUNDLISTWIDGET_H
