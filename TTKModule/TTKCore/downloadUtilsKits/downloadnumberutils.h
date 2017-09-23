#ifndef DOWNLOADNUMBERUTILS_H
#define DOWNLOADNUMBERUTILS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadnumberdefine.h"
#include "downloadglobaldefine.h"

/*! @brief The class of the utils number object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUtils
{
    namespace Number
    {
        /*!
         * Transform value to cp float value.
         */
        DOWNLOAD_UTILS_EXPORT QString size2Number(qint64 size);
        /*!
         * Transform value to cp int value.
         */
        DOWNLOAD_UTILS_EXPORT QString size2NumberInt(qint64 size);
        /*!
         * Transform value to cp value.
         */
        DOWNLOAD_UTILS_EXPORT QString size2Label(qint64 size);
        /*!
         * Transform value to speed float value.
         */
        DOWNLOAD_UTILS_EXPORT QString speed2Label(qint64 size);
        /*!
         * Transform value to speed int value.
         */
        DOWNLOAD_UTILS_EXPORT QString speed2LabelInt(qint64 size);

        /*!
         * Transform value to kb entity.
         */
        DOWNLOAD_UTILS_EXPORT qreal sizeByte2KByte(qint64 size);
        /*!
         * Transform value to mb entity.
         */
        DOWNLOAD_UTILS_EXPORT qreal sizeByte2MByte(qint64 size);
        /*!
         * Transform value to tb entity.
         */
        DOWNLOAD_UTILS_EXPORT qreal sizeByte2TByte(qint64 size);

        /*!
         * Transform value to speed value base.
         */
        DOWNLOAD_UTILS_EXPORT QString speed2LabelFromLabel(qint64 size, const QString &label);

    }
}

#endif // DOWNLOADNUMBERUTILS_H
