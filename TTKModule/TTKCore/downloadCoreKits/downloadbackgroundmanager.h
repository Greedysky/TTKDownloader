#ifndef DOWNLOADBACKGROUNDMANAGER_H
#define DOWNLOADBACKGROUNDMANAGER_H

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

#include <QColor>
#include "downloadsingleton.h"

#define M_BACKGROUND_PTR (DownloadSingleton<DownloadBackgroundManager>::createInstance())

#define MAX_INDEX 5

/*! @brief The class of the manager of dealing with artist pictures.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadBackgroundManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Add observer.
     */
    void addObserver(QObject *object);
    /*!
     * Remove observer.
     */
    void removeObserver(QObject *object);

    /*!
     * Set background picture by path.
     */
    void setMBackground(const QString &path);
    /*!
     * Get background picture path.
     */
    QString getMBackground() const;

    /*!
     * Set background picture color.
     */
    void setMBackgroundColor(const QColor &color);
    /*!
     * Get background picture color.
     */
    QColor getMBackgroundColor() const;

    /*!
     * Get artist background picture path.
     */
    void backgroundHasChanged();

Q_SIGNALS:
    /*!
     * Background image changed.
     */
    void backgroundChanged();

protected:
    /*!
     * Object contsructor.
     */
    DownloadBackgroundManager();

    QColor m_skinColor;
    QStringList m_photos;
    QList<QObject*> m_observer;
    QString m_background;

    DECLARE_SINGLETON_CLASS(DownloadBackgroundManager)
};

#endif // DOWNLOADBACKGROUNDMANAGER_H
