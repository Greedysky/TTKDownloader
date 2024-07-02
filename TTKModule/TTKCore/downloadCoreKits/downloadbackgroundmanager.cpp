#include "downloadbackgroundmanager.h"

DownloadBackgroundManager::DownloadBackgroundManager()
    : m_skinColor(Qt::white)
{

}

void DownloadBackgroundManager::addObserver(QObject *object)
{
    m_observer << object;
    connect(this, SIGNAL(backgroundChanged()), object, SLOT(backgroundChanged()));
}

void DownloadBackgroundManager::removeObserver(QObject *object)
{
    m_observer.removeAll(object);
    disconnect(this, SIGNAL(backgroundChanged()), object, SLOT(backgroundChanged()));
}

void DownloadBackgroundManager::setBackgroundUrl(const QString &path)
{
    m_background = path;
    Q_EMIT backgroundChanged();
}

QString DownloadBackgroundManager::backgroundUrl() const
{
    return m_background;
}

void DownloadBackgroundManager::setBackgroundColor(const QColor &color)
{
    m_skinColor = color;
}

QColor DownloadBackgroundManager::backgroundColor() const
{
    return m_skinColor;
}
