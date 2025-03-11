#include "downloadbackgroundmanager.h"

DownloadBackgroundManager::DownloadBackgroundManager() noexcept
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

void DownloadBackgroundManager::setBackgroundUrl(const QString &path) noexcept
{
    m_background = path;
    Q_EMIT backgroundChanged();
}

QString DownloadBackgroundManager::backgroundUrl() const noexcept
{
    return m_background;
}

void DownloadBackgroundManager::setBackgroundColor(const QColor &color) noexcept
{
    m_skinColor = color;
}

QColor DownloadBackgroundManager::backgroundColor() const noexcept
{
    return m_skinColor;
}
