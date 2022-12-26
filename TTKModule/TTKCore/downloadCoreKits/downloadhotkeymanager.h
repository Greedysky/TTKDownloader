#ifndef DOWNLOADHOTKEYMANAGER_H
#define DOWNLOADHOTKEYMANAGER_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2023 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "ttksingleton.h"
#include "ttkglobaldefine.h"

#define G_HOTKEY_PTR (TTKSingleton<DownloadHotKeyManager>::createInstance())

class QGlobalShortcut;

/*! @brief The class of the global hotkey setting manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadHotKeyManager : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadHotKeyManager)
public:
    /*!
     * To connect parent slot object.
     */
    void connectParentObject(QObject *object, const QString &sn, const char *slot);

    /*!
     * Set hotKey by given index and string key.
     */
    void setHotKey(int index, const QString &key);
    /*!
     * Set hotKey by given index and virtual key.
     */
    void setHotKey(int index, int key);
    /*!
     * Get the string key by given hotKey index.
     */
    QString hotKey(int index);

    /*!
     * Enable or disable the hotkey by index.
     */
    void setEnabled(int index, bool enabled);
    /*!
     * check the given hotkey is enabled or not.
     */
    bool enabled(int index);
    /*!
     * Enable or disable all hotkeys.
     */
    void enabledAll(bool enabled);

    /*!
     * Mapping the virtual key to string key.
     */
    QString toString(int key, int modifiers);
    /*!
     * Get hotkey count.
     */
    int count() const;

    /*!
     * Get key string.
     */
    QStringList keys() const;

private:
    QList<QGlobalShortcut*> m_hotkeys;

    TTK_DECLARE_SINGLETON_CLASS(DownloadHotKeyManager)

};

#endif // DOWNLOADHOTKEYMANAGER_H
