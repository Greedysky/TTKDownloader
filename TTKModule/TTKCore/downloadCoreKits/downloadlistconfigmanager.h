#ifndef DOWNLOADLISTCONFIGMANAGER_H
#define DOWNLOADLISTCONFIGMANAGER_H

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

#include "downloadabstractxml.h"

/*! @brief The class of the local download list item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_CORE_EXPORT DownloadList
{
    QString m_name;
    QString m_url;
}DownloadList;
TTK_DECLARE_LISTS(DownloadList)

/*! @brief The class of the download list manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadListConfigManager : public DownloadAbstractXml
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadListConfigManager(QObject *parent = nullptr);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Read list download datas from xml file by given name.
     */
    inline bool readListXMLConfig() { return readConfig(LISTPATH_FULL); }

    /*!
     * Write list download datas into xml file.
     */
    void writeListConfig(const DownloadLists &records);
    /*!
     * Read list download datas into xml file.
     */
    void readListConfig(DownloadLists &records);

};

#endif // DOWNLOADLISTCONFIGMANAGER_H
