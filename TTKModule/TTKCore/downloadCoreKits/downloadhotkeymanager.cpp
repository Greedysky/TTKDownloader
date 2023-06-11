#include "downloadhotkeymanager.h"
#include "qshortcut/qglobalshortcut.h"

#include <QStringList>

void DownloadHotKeyManager::setInputModule(QObject *object, const QString &sn, const char *slot)
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

void DownloadHotKeyManager::setHotKeys(const QStringList &keys)
{
    for(int i = 0; i < m_hotkeys.count(); ++i)
    {
        setHotKey(i, keys[i]);
        setEnabled(i, false);
    }
}

void DownloadHotKeyManager::addHotKey(int key)
{
    m_hotkeys << (new QGlobalShortcut(QKeySequence(key)));
}

void DownloadHotKeyManager::addHotKey(const QString &key)
{
    m_hotkeys << (new QGlobalShortcut(QKeySequence(key)));
}

QObject* DownloadHotKeyManager::hotKey(int index)
{
    if(index >= m_hotkeys.count())
    {
        return nullptr;
    }

    return m_hotkeys[index];
}

void DownloadHotKeyManager::unsetShortcut()
{
    for(QGlobalShortcut *key : qAsConst(m_hotkeys))
    {
        key->unsetShortcut();
        key->setEnabled(false);
    }
}

void DownloadHotKeyManager::setEnabled(bool enabled)
{
    for(QGlobalShortcut *key : qAsConst(m_hotkeys))
    {
        key->setEnabled(enabled);
    }
}

void DownloadHotKeyManager::setEnabled(int index, bool enabled)
{
    if(index >= m_hotkeys.count())
    {
        return;
    }

    m_hotkeys[index]->setEnabled(enabled);
}

bool DownloadHotKeyManager::isEnabled(int index)
{
    if(index >= m_hotkeys.count())
    {
        return false;
    }

    return m_hotkeys[index]->isEnabled();
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
