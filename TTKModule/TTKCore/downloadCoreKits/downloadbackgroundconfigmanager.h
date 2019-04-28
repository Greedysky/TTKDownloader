#ifndef DOWNLOADBACKGROUNDCONFIGMANAGER_H
#define DOWNLOADBACKGROUNDCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2019 Greedysky Studio

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

#include <QPixmap>
#include "downloadabstractxml.h"

/*! @brief The class of the skin config item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_CORE_EXPORT DownloadSkinConfigItem
{
    QString m_name;
    int m_useCount;

    DownloadSkinConfigItem()
    {
        m_name = "Greedysky";
        m_useCount = 8888;
    }

    bool isValid() const
    {
        return !(m_name.isEmpty() && m_useCount == 0);
    }

}DownloadSkinConfigItem;
TTK_DECLARE_LISTS(DownloadSkinConfigItem)

/*! @brief The class of the skin backgroud image item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_CORE_EXPORT DownloadBackgroundImage
{
    QPixmap m_pix;
    DownloadSkinConfigItem m_item;

    bool isValid() const
    {
        return !m_pix.isNull() && m_item.isValid();
    }

}DownloadBackgroundImage;
TTK_DECLARE_LISTS(DownloadBackgroundImage)


/*! @brief The class of the skin XML Config Manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadSkinConfigManager : public DownloadAbstractXml
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSkinConfigManager(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Write datas into xml file.
     */
    void writeSkinXMLConfig(const DownloadSkinConfigItem &item, const QString &path);
    /*!
     * Read datas into xml file.
     */
    void readSkinXMLConfig(DownloadSkinConfigItem &item);

};

#endif // DOWNLOADBACKGROUNDCONFIGMANAGER_H
