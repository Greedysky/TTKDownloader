#ifndef DOWNLOADBACKGROUNDCONFIGMANAGER_H
#define DOWNLOADBACKGROUNDCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

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
DOWNLOAD_DECLARE_LISTS(DownloadSkinConfigItem)

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
DOWNLOAD_DECLARE_LISTS(DownloadBackgroundImage)


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
