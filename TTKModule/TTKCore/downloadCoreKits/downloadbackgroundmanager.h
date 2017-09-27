#ifndef DOWNLOADBACKGROUNDMANAGER_H
#define DOWNLOADBACKGROUNDMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

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
