#ifndef DOWNLOADWIDGETUTILS_H
#define DOWNLOADWIDGETUTILS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

class QComboBox;

#include "downloadobject.h"
#include "downloadnumberdefine.h"
#include "downloadglobaldefine.h"

/*! @brief The class of the utils widget object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUtils
{
    namespace Widget
    {
        /*!
         * Set widget label font.
         */
        DOWNLOAD_UTILS_EXPORT void setLabelFontSize(QWidget *widget, int size);
        /*!
         * Set text elided text by font.
         */
        DOWNLOAD_UTILS_EXPORT QString elidedText(const QFont &font, const QString &text,
                                                 Qt::TextElideMode mode, int width);
        /*!
         * Set widget transparent.
         */
        DOWNLOAD_UTILS_EXPORT void setTransparent(QWidget *widget, int alpha);
        /*!
         * Set Combobox text.
         */
        DOWNLOAD_UTILS_EXPORT void setComboboxText(QComboBox *object, const QString &text);
        /*!
         * Set widget to round by ratioX and ratioY.
         */
        DOWNLOAD_UTILS_EXPORT void widgetToRound(QWidget *w, int ratioX, int ratioY);
        /*!
         * Set fusion two image.
         */
        DOWNLOAD_UTILS_EXPORT void fusionPixmap(QPixmap &bg, const QPixmap &fg, const QPoint &pt);
        /*!
         * Set pixmap to round by ratio.
         */
        DOWNLOAD_UTILS_EXPORT QPixmap pixmapToRound(const QPixmap &src, const QSize &size, int ratioX, int ratioY);
        /*!
         * Set pixmap to round by ratio.
         */
        DOWNLOAD_UTILS_EXPORT QPixmap pixmapToRound(const QPixmap &src, const QRect &rect, int ratioX, int ratioY);
        /*!
         * Set pixmap to round by ratio.
         */
        DOWNLOAD_UTILS_EXPORT QPixmap pixmapToRound(const QPixmap &src, const QPixmap &mask, const QSize &size);
        /*!
         * Get bitmap mask from rect.
         */
        DOWNLOAD_UTILS_EXPORT QBitmap getBitmapMask(const QRect &rect, int ratioX, int ratioY);
        /*!
         * Get pximap data.
         */
        DOWNLOAD_UTILS_EXPORT QByteArray getPixmapData(const QPixmap &pix);

        /*!
         * Rerender the custum value.
         */
        template<class T>
        DOWNLOAD_UTILS_EXPORT T reRenderValue(const T &key, const T &alpha, const T &value)
        {
            if(alpha < 0) return 0;
            else if(alpha > key) return key;

            return (key - alpha)*1.0/100*value + alpha;
        }

        /*!
         * Rerender the image alpha.
         */
        DOWNLOAD_UTILS_EXPORT int reRenderAlpha(int alpha, int value);
        /*!
         * Rerender the image by color burn transform.
         */
        DOWNLOAD_UTILS_EXPORT void reRenderImage(int delta, const QImage *input, QImage *output);
        /*!
         * Rerender the image by color burn transform.
         */
        DOWNLOAD_UTILS_EXPORT void reRenderImage(qint64 &avg, int delta, const QImage *input, QImage *output);
        /*!
         * Image color burn transform.
         */
        DOWNLOAD_UTILS_EXPORT uint colorBurnTransform(int c, int delta);

        /*!
         * Get open file dialog.
         */
        DOWNLOAD_UTILS_EXPORT QString getOpenFileDialog(QWidget *obj, const QString &title, const QString &filter);
        /*!
         * Get open file dialog.
         */
        DOWNLOAD_UTILS_EXPORT QString getOpenFileDialog(QWidget *obj, const QString &filter);
        /*!
         * Get open file dialog.
         */
        DOWNLOAD_UTILS_EXPORT QString getOpenFileDialog(QWidget *obj);

        /*!
         * Get open files dialog.
         */
        DOWNLOAD_UTILS_EXPORT QStringList getOpenFilesDialog(QWidget *obj, const QString &title, const QString &filter);
        /*!
         * Get open files dialog.
         */
        DOWNLOAD_UTILS_EXPORT QStringList getOpenFilesDialog(QWidget *obj, const QString &filter);
        /*!
         * Get open files dialog.
         */
        DOWNLOAD_UTILS_EXPORT QStringList getOpenFilesDialog(QWidget *obj);

        /*!
         * Get save file dialog.
         */
        DOWNLOAD_UTILS_EXPORT QString getSaveFileDialog(QWidget *obj, const QString &title, const QString &filter);
        /*!
         * Get save file dialog.
         */
        DOWNLOAD_UTILS_EXPORT QString getSaveFileDialog(QWidget *obj, const QString &filter);
        /*!
         * Get save file dialog.
         */
        DOWNLOAD_UTILS_EXPORT QString getSaveFileDialog(QWidget *obj);

    }
}

#endif // DOWNLOADWIDGETUTILS_H
