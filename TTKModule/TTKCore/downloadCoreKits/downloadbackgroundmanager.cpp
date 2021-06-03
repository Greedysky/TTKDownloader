#include "downloadbackgroundmanager.h"

#define MAX_INDEX 5

DownloadBackgroundManager::DownloadBackgroundManager()
{
    m_skinColor = QColor(Qt::white);
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

void DownloadBackgroundManager::setMBackground(const QString &path)
{
    m_background = path;
}

QString DownloadBackgroundManager::getMBackground() const
{
    return m_background;
}

void DownloadBackgroundManager::setMBackgroundColor(const QColor &color)
{
    m_skinColor = color;
}

QColor DownloadBackgroundManager::getMBackgroundColor() const
{
    return m_skinColor;
}

void DownloadBackgroundManager::backgroundHasChanged()
{
    emit backgroundChanged();
}
