#ifndef DOWNLOADSINGLETON_H
#define DOWNLOADSINGLETON_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QMutex>
#include <QObject>
#include <QScopedPointer>
#include "downloadglobaldefine.h"

template <typename T>
/*! @brief The class of the singleton base.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadSingleton
{
public:
    /*!
     * Get object instance ptr.
     */
    static T* createInstance();
    /*!
     * Get class object name.
     */
    static QString getClassName();

private:
    /*!
     * Object contsructor.
     */
    DownloadSingleton(){}

    ~DownloadSingleton(){}

    static QMutex m_mutex;
    static QScopedPointer<T> m_instance;
    Q_DISABLE_COPY(DownloadSingleton)

};

    ////////////////////////////////////////////////////////////////
    ///                                                           //
    ///              Singleton Implementation                     //
    ///                                                           //
    ////////////////////////////////////////////////////////////////

template<typename T> QMutex DownloadSingleton<T>::m_mutex;
template<typename T> QScopedPointer<T> DownloadSingleton<T>::m_instance;

template<typename T>
T* DownloadSingleton<T>::createInstance()
{
    if(m_instance.isNull())
    {
        m_mutex.lock();
        if(m_instance.isNull())
        {
            m_instance.reset(new T());
        }
        m_mutex.unlock();
    }
    return m_instance.data();
}

template<typename T>
QString DownloadSingleton<T>::getClassName()
{
    return "DownloadSingleton";
}

    ////////////////////////////////////////////////////////////////
    ///                                                           //
    ///              Singleton Macro                              //
    ///                                                           //
    ////////////////////////////////////////////////////////////////

////Class that will implement the singleton mode,
////must use the macro in it's delare file
#define DECLARE_SINGLETON_CLASS( Class )             \
    friend class DownloadSingleton<Class>;              \
    friend struct QScopedPointerDeleter<Class>;

#endif // DOWNLOADSINGLETON

