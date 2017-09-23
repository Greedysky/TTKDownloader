#include "downloadlockedfile.h"

DownloadLockedFile::DownloadLockedFile()
    : QFile()
{
#ifdef Q_OS_WIN
    wmutex = 0;
    rmutex = 0;
#endif
    m_lock_mode = NoLock;
}

DownloadLockedFile::DownloadLockedFile(const QString &name)
    : QFile(name)
{
#ifdef Q_OS_WIN
    wmutex = 0;
    rmutex = 0;
#endif
    m_lock_mode = NoLock;
}

bool DownloadLockedFile::open(OpenMode mode)
{
    if (mode & QIODevice::Truncate) {
        qWarning("DownloadLockedFile::open(): Truncate mode not allowed.");
        return false;
    }
    return QFile::open(mode);
}

bool DownloadLockedFile::isLocked() const
{
    return m_lock_mode != NoLock;
}

DownloadLockedFile::LockMode DownloadLockedFile::lockMode() const
{
    return m_lock_mode;
}
