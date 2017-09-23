#ifndef DOWNLOADLOCKEDFILE_H
#define DOWNLOADLOCKEDFILE_H

#include <QFile>
#ifdef Q_OS_WIN
#include <QVector>
#endif
#include "downloadrunglobaldefine.h"

namespace DownloadLockedPrivate {
  /*! @brief The class of the download local file.
   * @author Greedysky <greedysky@163.com>
   */
    class DOWNLOAD_RUN_EXPORT DownloadLockedFile : public QFile
    {
    public:
        enum LockMode
        {
            NoLock = 0,
            ReadLock,
            WriteLock
        };

        DownloadLockedFile();
       /*!
         * Object contsructor.
        */
        explicit DownloadLockedFile(const QString &name);
        /*!
         * Object contsructor.
        */
        ~DownloadLockedFile();

        bool open(OpenMode mode);
        /*!
         * Open current locked file.
        */
        
        bool lock(LockMode mode, bool block = true);
        /*!
         * Lock current file.
        */
        bool unlock();
        /*!
         * Unlock current file.
        */
        bool isLocked() const;
        /*!
         * Get current lock status.
        */
        LockMode lockMode() const;
        /*!
         * Get current lock file mode.
        */
        
    private:
    #ifdef Q_OS_WIN
        Qt::HANDLE wmutex;
        Qt::HANDLE rmutex;
        QVector<Qt::HANDLE> rmutexes;
        QString mutexname;

        Qt::HANDLE getMutexHandle(int idx, bool doCreate);
        bool waitMutex(Qt::HANDLE mutex, bool doBlock);

    #endif
        LockMode m_lock_mode;
    };
}
#endif //DOWNLOADLOCKEDFILE_H
