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
    TTK_DECLARE_SINGLETON_CLASS(DownloadSettingManager)
public:
    enum Config
    {
        Null = -1,                          /*!< No parameter */
        ScreenSize = 0x1000,                /*!< Screen size parameter */
        WidgetPosition = 0x1001,            /*!< Widget position parameter */
        WidgetSize = 0x1002,                /*!< Widget size parameter */
        ExpandMode = 0x1003,                /*!< Expand mode parameter */
        //
        CloseEventMode = 0x2000,            /*!< Close event parameter */
        StartUpMode = 0x2001,               /*!< Start up mode parameter */
        StartUpRunMode = 0x2002,            /*!< Start up run mode parameter */
        SlienceRunMode = 0x2003,            /*!< Slience run mode parameter */
        LogTrackEnable = 0x2004,            /*!< Log track enable parameter */
        UserPermission = 0x2005,            /*!< User permission parameter */
        //
        BackgroundThemeValue = 0x3000,      /*!< Background theme parameter */
        BackgroundTransparent = 0x3001,     /*!< Background transparent parameter */
        //
        HotkeyEnable = 0x4000,              /*!< Hotkey enable parameter */
        HotkeyValue = 0x4001,               /*!< Hotkey string parameter */
        //
        DownloadMode = 0x5000,              /*!< Download mode parameter */
        DownloadMaxCount = 0x5001,          /*!< Download max count parameter */
        DownloadLimit = 0x5002,             /*!< Download limit parameter */
        DownloadPathDir = 0x5003,           /*!< Download path dir parameter */
        DownloadDLoadLimit = 0x5004,        /*!< Download dload limit parameter */
        DownloadULoadLimit = 0x5005,        /*!< Download uload limit parameter */
        //
        SkinEffectLevel = 0x6000,           /*!< Skin effect level parameter */
        SkinSuspension = 0x6001,            /*!< Skin suspension show parameter */
        SkinSuspensionValue = 0x6002,       /*!< Skin suspension show value parameter */
    };

    /*!
     * Set current value by Config Type.
     */
    inline void setValue(Config type, const QVariant &var) noexcept
    {
        m_parameter[type] = var;
    }

    /*!
     * Set current value by String Type.
     */
    inline void setValue(const QString &stype, const QVariant &var) noexcept
    {
        m_parameter[stringToEnum(stype)] = var;
    }

    /*!
     * Get current value by Config Type.
     */
    inline QVariant value(Config type) const noexcept
    {
        return m_parameter[type];
    }

    /*!
     * Get current value by String Type.
     */
    inline QVariant value(const QString &stype) const noexcept
    {
        return m_parameter[stringToEnum(stype)];
    }

    /*!
     * Get parameter count.
     */
    inline int count() const noexcept
    {
        return m_parameter.count();
    }

    /*!
     * Current parameter is empty.
     */
    inline bool isEmpty() const noexcept
    {
        return m_parameter.isEmpty();
    }

    /*!
     * Current parameter contains type.
     */
    inline bool contains(Config type) const noexcept
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

};

#endif // DOWNLOADSETTINGMANAGER
