#ifndef DOWNLOADSYSCONFIGMANAGER_H
#define DOWNLOADSYSCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QColor>
#include "downloadabstractxml.h"

/*! @brief The class of the sys xml config manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadSysConfigManager : public DownloadAbstractXml
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSysConfigManager(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Read config datas from xml file by given name.
     */
    inline bool readXMLConfig() { return readConfig(COFIGPATH_FULL); }

    /*!
     * Write datas into xml file.
     */
    void writeXMLConfig();

    /*!
     * Read window widget Geometry Config.
     */
    QRect readWindowGeometry() const;
    /*!
     * Read Sys Load Config.
     */
    void readSysLoadConfig() const;

};

#endif // DOWNLOADSYSCONFIGMANAGER_H
