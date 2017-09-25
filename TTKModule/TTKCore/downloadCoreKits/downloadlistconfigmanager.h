#ifndef DOWNLOADLISTCONFIGMANAGER_H
#define DOWNLOADLISTCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractxml.h"

/*! @brief The class of the local download list item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_SUPER_EXPORT DownloadList
{
    QString m_url;
}DownloadList;
DOWNLOAD_DECLARE_LISTS(DownloadList)

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
    explicit DownloadListConfigManager(QObject *parent = 0);

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
