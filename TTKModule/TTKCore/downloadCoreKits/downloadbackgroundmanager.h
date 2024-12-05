#ifndef DOWNLOADBACKGROUNDMANAGER_H
#define DOWNLOADBACKGROUNDMANAGER_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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
 ***************************************************************************/

#include <QColor>
#include "ttksingleton.h"

#define G_BACKGROUND_PTR (TTKSingleton<DownloadBackgroundManager>::instance())

/*! @brief The class of the manager of dealing with artist pictures.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBackgroundManager : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadBackgroundManager)
public:
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
    void setBackgroundUrl(const QString &path);
    /*!
     * Get background picture path.
     */
    QString backgroundUrl() const;

    /*!
     * Set background picture color.
     */
    void setBackgroundColor(const QColor &color);
    /*!
     * Get background picture color.
     */
    QColor backgroundColor() const;

Q_SIGNALS:
    /*!
     * Background image changed.
     */
    void backgroundChanged();

private:
    /*!
     * Object constructor.
     */
    DownloadBackgroundManager();

    QColor m_skinColor;
    QObjectList m_observer;
    QString m_background;

    TTK_DECLARE_SINGLETON_CLASS(DownloadBackgroundManager)

};

#endif // DOWNLOADBACKGROUNDMANAGER_H
