#ifndef DOWNLOADBREAKPOINTCONFIGMANAGER_H
#define DOWNLOADBREAKPOINTCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractxml.h"

/*! @brief The class of the break point item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_CORE_EXPORT DownloadBreakPointItem
{
    QString m_url;
    qint64 m_start;
    qint64 m_end;
    qint64 m_ready;

    DownloadBreakPointItem()
    {
        m_start = 0;
        m_end = 0;
        m_ready = 0;
    }

    bool isEmpty() const
    {
        return m_start == 0 && m_end == 0 && m_ready == 0;
    }
}DownloadBreakPointItem;
DOWNLOAD_DECLARE_LISTS(DownloadBreakPointItem)

/*! @brief The class of the break point config manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadBreakPointConfigManager : public DownloadAbstractXml
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBreakPointConfigManager(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Write datas into xml file.
     */
    void writeBreakPointConfig(const DownloadBreakPointItems &records);
    /*!
     * Read datas into xml file.
     */
    void readBreakPointConfig(DownloadBreakPointItems &records);

};

#endif // DOWNLOADBREAKPOINTCONFIGMANAGER_H
