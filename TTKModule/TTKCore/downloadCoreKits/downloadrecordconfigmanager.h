#ifndef DOWNLOADRECORDCONFIGMANAGER_H
#define DOWNLOADRECORDCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractxml.h"

/*! @brief The class of the local download record item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_SUPER_EXPORT DownloadRecord
{
    QString m_time;
    QString m_path;
    QString m_size;
}DownloadRecord;
DOWNLOAD_DECLARE_LISTS(DownloadRecord)

/*! @brief The class of the download record manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadRecordConfigManager : public DownloadAbstractXml
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadRecordConfigManager(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Read history download datas from xml file by given name.
     */
    inline bool readDownloadXMLConfig() { return readConfig(HISTORYPATH_FULL); }

    /*!
     * Write history download datas into xml file.
     */
    void writeDownloadConfig(const DownloadRecords &records);
    /*!
     * Read history download datas into xml file.
     */
    void readDownloadConfig(DownloadRecords &records);

};

#endif // DOWNLOADRECORDCONFIGMANAGER_H
