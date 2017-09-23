#include "downloadhotkeymanager.h"
#include "qshortcut/qxtglobalshortcut.h"

#include <QStringList>

QString DownloadHotKeyManager::getClassName()
{
    return staticMetaObject.className();
}

void DownloadHotKeyManager::setDefaultKey()
{
    QStringList keys(getDefaultKeys());
    for(int i=0; i<m_hotkeys.count(); ++i)
    {
        setHotKey(i, keys[i]);
        setEnabled(i, false);
    }
}

void DownloadHotKeyManager::setHotKeys(const QStringList &keys)
{
    for(int i=0; i<m_hotkeys.count(); ++i)
    {
        setHotKey(i, keys[i]);
        setEnabled(i, false);
    }
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
    foreach(QxtGlobalShortcut *key, m_hotkeys)
    {
        key->setEnabled(enabled);
    }
}

QString DownloadHotKeyManager::toString(int key, int modifiers)
{
    QString strModList[] = { "Ctrl", "Shift", "Alt"};
    quint32 modList[] = { Qt::ControlModifier, Qt::ShiftModifier, Qt::AltModifier};

    QString keyStr;
    for(int j=0; j<3; j++)
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

QStringList DownloadHotKeyManager::getDefaultKeys() const
{
    QStringList keys;
    keys << "Ctrl+B" << "Ctrl+Left" << "Ctrl+Right" << "Ctrl+Up"
         << "Ctrl+Down" << "Ctrl+S" << "Ctrl+I" << "Ctrl+M";
    return keys;
}

QStringList DownloadHotKeyManager::getKeys() const
{
    QStringList keys;
    foreach(QxtGlobalShortcut *key, m_hotkeys)
    {
        keys << key->shortcut().toString();
    }
    return keys;
}
