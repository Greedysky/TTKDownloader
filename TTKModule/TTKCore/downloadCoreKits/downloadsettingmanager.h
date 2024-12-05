#ifndef DOWNLOADSETTINGMANAGER
#define DOWNLOADSETTINGMANAGER

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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

#include <QMetaEnum>
#include "downloadobject.h"
#include "ttksingleton.h"

#define G_SETTING_PTR (TTKSingleton<DownloadSettingManager>::instance())

/*! @brief The class of the paramater setting manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadSettingManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(Config)
    TTK_DECLARE_MODULE(DownloadSettingManager)
public:
    enum Config
    {
        Null = -1,                          /*!< No Parameter*/
        ScreenSize = 0x1000,                /*!< Screen Size Parameter*/
        WidgetPosition = 0x1001,            /*!< Widget Position Parameter*/
        WidgetSize = 0x1002,                /*!< Widget Size Parameter*/
        //
        CloseEventMode = 0x2000,            /*!< Close Event Parameter*/
        CloseNetWorkMode = 0x2001,          /*!< Close NetWork Parameter*/
        FileAssociationMode = 0x2002,       /*!< File Association Parameter*/
        StartUpMode = 0x2003,               /*!< Start Up Mode Parameter*/
        StartUpRunMode = 0x2004,            /*!< Start Up Run Mode Parameter*/
        SlienceRunMode = 0x2005,            /*!< Slience Run Mode Parameter*/
        ExpandMode = 0x2006,                /*!< Expand Mode Parameter*/
        //
        BackgroundThemeValue = 0x3000,      /*!< Background Theme Parameter*/
        BackgroundTransparent = 0x3001,     /*!< Background Transparent Parameter*/
        //
        HotkeyEnable = 0x4000,              /*!< Hotkey Enable Parameter*/
        HotkeyValue = 0x4001,               /*!< Hotkey String Parameter*/
        //
        DownloadMode = 0x5000,              /*!< Download Mode Parameter*/
        DownloadMaxCount = 0x5001,          /*!< Download Max Count Parameter*/
        DownloadLimit = 0x5002,             /*!< Download Limit Parameter*/
        DownloadPathDir = 0x5003,           /*!< Download Path Dir Parameter*/
        DownloadDLoadLimit = 0x5004,        /*!< Download DLoad Limit Parameter*/
        DownloadULoadLimit = 0x5005,        /*!< Download ULoad Limit Parameter*/
        //
        SkinEffectLevel = 0x6000,           /*!< Skin effect Level Parameter*/
        SkinSuspension = 0x6001,            /*!< Skin Suspension Show Parameter*/
        SkinSuspensionValue = 0x6002,       /*!< Skin Suspension Show Value Parameter*/
    };

    /*!
     * Set current value by Config Type.
     */
    inline void setValue(Config type, const QVariant &var)
    {
        m_parameter[type] = var;
    }

    /*!
     * Set current value by String Type.
     */
    inline void setValue(const QString &stype, const QVariant &var)
    {
        m_parameter[stringToEnum(stype)] = var;
    }

    /*!
     * Get current value by Config Type.
     */
    inline QVariant value(Config type) const
    {
        return m_parameter[type];
    }

    /*!
     * Get current value by String Type.
     */
    inline QVariant value(const QString &stype) const
    {
        return m_parameter[stringToEnum(stype)];
    }

    /*!
     * Get parameter count.
     */
    inline int count() const
    {
        return m_parameter.count();
    }

    /*!
     * Current parameter is empty.
     */
    inline bool isEmpty() const
    {
        return m_parameter.isEmpty();
    }

    /*!
     * Current parameter contains type.
     */
    inline bool contains(Config type) const
    {
        return m_parameter.contains(type);
    }

private:
    /*!
     * Convert String type to Config Type.
     */
    inline Config stringToEnum(const QString &stype) const
    {
        int index = staticMetaObject.indexOfEnumerator("Config");
        QMetaEnum metaEnum = staticMetaObject.enumerator(index);
        int key = metaEnum.keyToValue(stype.toStdString().c_str());
        return TTKStaticCast(Config, key);
    }

    QVariant m_variant;
    QMap<Config, QVariant> m_parameter;

    TTK_DECLARE_SINGLETON_CLASS(DownloadSettingManager)

};

#endif // DOWNLOADSETTINGMANAGER
