#include "downloadhotkeymanager.h"
#include "qshortcut/qglobalshortcut.h"

#include <QStringList>

void DownloadHotKeyManager::connectParentObject(QObject *object, const QString &sn, const char *slot)
{
    QGlobalShortcut *hotkey = new QGlobalShortcut(object);
    connect(hotkey, SIGNAL(activated()), object, slot);

    m_hotkeys << hotkey;
    setHotKey(m_hotkeys.count() - 1, sn);
    setEnabled(m_hotkeys.count() - 1, true);
}

void DownloadHotKeyManager::setHotKey(int index, const QString &key)
{
    if(index >= m_hotkeys.count())
    {
        return;
    }
    m_hotkeys[index]->setShortcut(QKeySequence(key));
}

void DownloadHotKeyManager::setHotKey(int index, int key)
{
    if(index >= m_hotkeys.count())
    {
        return;
    }
    m_hotkeys[index]->setShortcut(QKeySequence(key));
}

QString DownloadHotKeyManager::hotKey(int index)
{
    if(index >= m_hotkeys.count())
    {
        return QString();
    }
    return m_hotkeys[index]->shortcut().toString();
}

void DownloadHotKeyManager::setEnabled(int index, bool enabled)
{
    if(index >= m_hotkeys.count())
    {
        return;
    }
    m_hotkeys[index]->setEnabled(enabled);
}

bool DownloadHotKeyManager::enabled(int index)
{
    if(index >= m_hotkeys.count())
    {
        return false;
    }
    return m_hotkeys[index]->isEnabled();
}

void DownloadHotKeyManager::enabledAll(bool enabled)
{
    for(QGlobalShortcut *key : qAsConst(m_hotkeys))
    {
        key->setEnabled(enabled);
    }
}

QString DownloadHotKeyManager::toString(int key, int modifiers)
{
    QString strModList[] = { "Ctrl", "Shift", "Alt"};
    quint32 modList[] = { Qt::ControlModifier, Qt::ShiftModifier, Qt::AltModifier};

    QString keyStr;
    for(int j = 0; j < 3; ++j)
    {
        if(modifiers & modList[j])
        {
            keyStr.append(strModList[j] + "+");
        }
    }

    if(key == Qt::Key_Shift || key == Qt::Key_Control || key == Qt::Key_Alt)
    {
        keyStr.chop(1);
        return keyStr;
    }

    return keyStr + QKeySequence(key).toString();
}

int DownloadHotKeyManager::count() const
{
    return m_hotkeys.count();
}

QStringList DownloadHotKeyManager::keys() const
{
    QStringList keys;
    for(QGlobalShortcut *key : qAsConst(m_hotkeys))
    {
        keys << key->shortcut().toString();
    }
    return keys;
}
