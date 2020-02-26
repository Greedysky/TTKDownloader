#ifndef DOWNLOADSETTINGMANAGER
#define DOWNLOADSETTINGMANAGER

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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
 ================================================= */

#include <QMetaEnum>
#include "downloadobject.h"
#include "downloadsingleton.h"

#define M_SETTING_PTR (DownloadSingleton<DownloadSettingManager>::createInstance())

/*! @brief The class of the paramater setting manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadSettingManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(ConfigType)
public:
    enum ConfigType
    {
        Null = -1,                      /*!< No Parameter*/
        ScreenSize,                     /*!< Screen Size Parameter*/
        WidgetPosition,                 /*!< Widget Position Parameter*/
        WidgetSize,                     /*!< Widget Size Parameter*/

        CloseEventChoiced,              /*!< Close Event Parameter*/
        CloseNetWorkChoiced,            /*!< Close NetWork Parameter*/
        FileAssociationChoiced,         /*!< File Association Parameter*/
        StartUpModeChoiced,             /*!< Start Up Mode Parameter*/
        StartUpRunModeChoiced,          /*!< Start Up Run Mode Parameter*/
        SlienceRunModeChoiced,          /*!< Slience Run Mode Parameter*/
        ExpandModeChoiced,              /*!< Expand Mode Parameter*/

        BgThemeChoiced,                 /*!< Bg Theme Parameter*/
        BgTransparentChoiced,           /*!< Bg Transparent Parameter*/

        DownloadModeChoiced,            /*!< Download Mode Parameter*/
        DownloadMaxCountChoiced,        /*!< Download Max Count Parameter*/
        DownloadLimitChoiced,           /*!< Download Limit Parameter*/
        DownloadPathDirChoiced,         /*!< Download Path Dir Parameter*/
        DownloadDLoadLimitChoiced,      /*!< Download DLoad Limit Parameter*/
        DownloadULoadLimitChoiced,      /*!< Download ULoad Limit Parameter*/

        SkinEffectLevelChoiced,         /*!< Skin effect Level Parameter*/
        SkinFontChoiced,                /*!< Skin Font Parameter*/
        SkinSuspensionChoiced,          /*!< Skin Suspension Show Parameter*/
        SkinSuspensionPerChoiced        /*!< Skin Suspension Show Percent Parameter*/

    };

    /*!
     * Get class object name.
     */
    static QString getClassName()
    {
        return staticMetaObject.className();
    }

    /*!
     * Set current value by Config Type.
     */
    inline void setValue(ConfigType type, const QVariant &var)
    {
        m_para[type] = var;
    }

    /*!
     * Set current value by String Type.
     */
    inline void setValue(const QString &stype, const QVariant &var)
    {
        m_para[typeStringToEnum(stype)] = var;
    }

    /*!
     * Get current value by Config Type.
     */
    inline QVariant value(ConfigType type) const
    {
        return m_para[type];
    }

    /*!
     * Get current value by String Type.
     */
    inline QVariant value(const QString &stype) const
    {
        return m_para[typeStringToEnum(stype)];
    }

    /*!
     * Get parameter count.
     */
    inline int count() const
    {
        return m_para.count();
    }

    /*!
     * Current parameter is empty.
     */
    inline bool isEmpty() const
    {
        return m_para.isEmpty();
    }

    /*!
     * Current parameter contains type.
     */
    inline bool contains(ConfigType type) const
    {
        return m_para.contains(type);
    }

protected:
    /*!
     * Convert String type to Config Type.
     */
    ConfigType typeStringToEnum(const QString &stype) const
    {
        int index = staticMetaObject.indexOfEnumerator("ConfigType");
        QMetaEnum metaEnum = staticMetaObject.enumerator(index);
        int key = metaEnum.keyToValue(stype.toStdString().c_str());
        return TTKStatic_cast(ConfigType, key);
    }

    QVariant m_variant;
    QMap<ConfigType, QVariant> m_para;

    DECLARE_SINGLETON_CLASS(DownloadSettingManager)
};


#endif // DOWNLOADSETTINGMANAGER
