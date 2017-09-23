#ifndef DOWNLOADSETTINGMANAGER
#define DOWNLOADSETTINGMANAGER

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

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
        WindowQuitModeChoiced,          /*!< Window Quit Mode Parameter*/

        BgThemeChoiced,                 /*!< Bg Theme Parameter*/
        BgTransparentChoiced,           /*!< Bg Transparent Parameter*/

        DownloadLimitChoiced,           /*!< Download Limit Parameter*/
        DownloadDLoadLimitChoiced,      /*!< Download DLoad Limit Parameter*/
        DownloadULoadLimitChoiced,      /*!< Download ULoad Limit Parameter*/

        HotkeyEnableChoiced,            /*!< Hotkey Enable Parameter*/
        HotkeyStringChoiced             /*!< Hotkey String Parameter*/

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
        return MStatic_cast(ConfigType, key);
    }

    QVariant m_variant;
    QMap<ConfigType, QVariant> m_para;

    DECLARE_SINGLETON_CLASS(DownloadSettingManager)
};


#endif // DOWNLOADSETTINGMANAGER
