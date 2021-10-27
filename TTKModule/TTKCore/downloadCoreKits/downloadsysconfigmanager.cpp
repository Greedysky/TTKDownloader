#include "downloadsysconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadcoreutils.h"

#include <QRect>

DownloadSysConfigManager::DownloadSysConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadSysConfigManager::writeXMLConfig()
{
    QPoint widgetPositionChoiced = G_SETTING_PTR->value(DownloadSettingManager::WidgetPosition).toPoint();
    QSize widgetSizeChoiced = G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize();
    int closeEventChoiced = G_SETTING_PTR->value(DownloadSettingManager::CloseEventChoiced).toInt();
    int closeNetWorkChoiced = G_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkChoiced).toInt();
    int fileAssociationChoiced = G_SETTING_PTR->value(DownloadSettingManager::FileAssociationChoiced).toInt();
    int startupModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::StartUpModeChoiced).toInt();
    int startupRunModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::StartUpRunModeChoiced).toInt();
    int slienceRunModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::SlienceRunModeChoiced).toInt();

    ///////////////////////////////////////////////////////////////////////////
    QString bgThemeChoiced = G_SETTING_PTR->value(DownloadSettingManager::BgThemeChoiced).toString();
    int bgTransparentChoiced = G_SETTING_PTR->value(DownloadSettingManager::BgTransparentChoiced).toInt();

    ///////////////////////////////////////////////////////////////////////////
    int downloadLimit = G_SETTING_PTR->value(DownloadSettingManager::DownloadLimitChoiced).toInt();
    int downloadModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::DownloadModeChoiced).toInt();
    int downloadMaxCountChoiced = G_SETTING_PTR->value(DownloadSettingManager::DownloadMaxCountChoiced).toInt();
    QString downloadPathDir = G_SETTING_PTR->value(DownloadSettingManager::DownloadPathDirChoiced).toString();
    QString downloadDLoadLimit = G_SETTING_PTR->value(DownloadSettingManager::DownloadDLoadLimitChoiced).toString();
    QString downloadULoadLimit = G_SETTING_PTR->value(DownloadSettingManager::DownloadULoadLimitChoiced).toString();

    ///////////////////////////////////////////////////////////////////////////
    int skinEffectLevelChoiced = G_SETTING_PTR->value(DownloadSettingManager::SkinEffectLevelChoiced).toInt();
    int skinFontChoiced = G_SETTING_PTR->value(DownloadSettingManager::SkinFontChoiced).toInt();
    int skinSuspensionChoiced = G_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionChoiced).toInt();
    int skinSuspensionPerChoiced = G_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionPerChoiced).toInt();

    ///////////////////////////////////////////////////////////////////////////

    //Open wirte file
    if(!writeConfig(COFIG_PATH_FULL))
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement playerDom = createRoot(APP_NAME);
    //Class A
    QDomElement plusSettingDom = writeDom(playerDom, "plusSetting");
    QDomElement backgroundSettingDom = writeDom(playerDom, "backgroundSetting");
    QDomElement downloadSettingDom = writeDom(playerDom, "downloadSetting");
    QDomElement skinSettingDom = writeDom(playerDom, "skinSetting");
    //Class B

    ///////////////////////////////////////////////////////////////////////////
    writeDomElement(plusSettingDom, "geometry", DownloadXmlAttribute("value", QString("%1,%2,%3,%4").arg(widgetPositionChoiced.x())
                    .arg(widgetPositionChoiced.y()).arg(widgetSizeChoiced.width()).arg(widgetSizeChoiced.height())));
    writeDomElement(plusSettingDom, "closeEvent", DownloadXmlAttribute("value", closeEventChoiced));
    writeDomElement(plusSettingDom, "closeNetwork", DownloadXmlAttribute("value", closeNetWorkChoiced));
    writeDomElement(plusSettingDom, "fileAssociation", DownloadXmlAttribute("value", fileAssociationChoiced));
    writeDomElement(plusSettingDom, "startUpMode", DownloadXmlAttribute("value", startupModeChoiced));
    writeDomElement(plusSettingDom, "startUpRunMode", DownloadXmlAttribute("value", startupRunModeChoiced));
    writeDomElement(plusSettingDom, "slienceRunMode", DownloadXmlAttribute("value", slienceRunModeChoiced));

    ///////////////////////////////////////////////////////////////////////////
    writeDomElement(backgroundSettingDom, "bgTheme", DownloadXmlAttribute("value", bgThemeChoiced));
    writeDomElement(backgroundSettingDom, "bgTransparent", DownloadXmlAttribute("value", bgTransparentChoiced));

    ///////////////////////////////////////////////
    writeDomElement(downloadSettingDom, "downloadLimit", DownloadXmlAttribute("value", downloadLimit));
    writeDomElement(downloadSettingDom, "downloadMode", DownloadXmlAttribute("value", downloadModeChoiced));
    writeDomElement(downloadSettingDom, "downloadMaxCount", DownloadXmlAttribute("value", downloadMaxCountChoiced));
    writeDomElement(downloadSettingDom, "downloadPathDir", DownloadXmlAttribute("value", downloadPathDir));
    writeDomElement(downloadSettingDom, "downloadDLoadLimit", DownloadXmlAttribute("value", downloadDLoadLimit));
    writeDomElement(downloadSettingDom, "downloadULoadLimit", DownloadXmlAttribute("value", downloadULoadLimit));

    ///////////////////////////////////////////////
    writeDomElement(skinSettingDom, "skinEffectLevel", DownloadXmlAttribute("value", skinEffectLevelChoiced));
    writeDomElement(skinSettingDom, "skinFont", DownloadXmlAttribute("value", skinFontChoiced));
    writeDomElement(skinSettingDom, "skinSuspension", DownloadXmlAttribute("value", skinSuspensionChoiced));
    writeDomElement(skinSettingDom, "skinSuspensionPer", DownloadXmlAttribute("value", skinSuspensionPerChoiced));


    //Write to file
    QTextStream out(m_file);
    m_ddom->save(out, 4);
}

QRect DownloadSysConfigManager::readWindowGeometry() const
{
    QDomNodeList nodelist = m_ddom->elementsByTagName("geometry");
    if(nodelist.isEmpty())
    {
        return QRect(0, 0, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    }

    QDomElement element = nodelist.at(0).toElement();
    QStringList list = element.attribute("value").split(",");
    if(list.count() == 4)
    {
        return QRect(list[0].toInt() < 0 ? 0 : list[0].toInt(),
                     list[1].toInt() < 0 ? 0 : list[1].toInt(),
                     list[2].toInt(), list[3].toInt());
    }
    else
    {
        return QRect(0, 0, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    }
}

void DownloadSysConfigManager::readSysLoadConfig() const
{
    G_SETTING_PTR->setValue(DownloadSettingManager::CloseEventChoiced,
                     readXmlAttributeByTagNameValue("closeEvent").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::CloseNetWorkChoiced,
                     readXmlAttributeByTagNameValue("closeNetwork").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::FileAssociationChoiced,
                     readXmlAttributeByTagNameValue("fileAssociation").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpModeChoiced,
                     readXmlAttributeByTagNameValue("startUpMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpRunModeChoiced,
                     readXmlAttributeByTagNameValue("startUpRunMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::SlienceRunModeChoiced,
                     readXmlAttributeByTagNameValue("slienceRunMode").toInt());


    G_SETTING_PTR->setValue(DownloadSettingManager::BgThemeChoiced,
                     readXmlAttributeByTagNameValue("bgTheme"));
    G_SETTING_PTR->setValue(DownloadSettingManager::BgTransparentChoiced,
                     readXmlAttributeByTagNameValue("bgTransparent").toInt());


    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadLimit").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadModeChoiced,
                     readXmlAttributeByTagNameValue("downloadMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMaxCountChoiced,
                     readXmlAttributeByTagNameValue("downloadMaxCount").toInt());
    QString path = readXmlAttributeByTagNameValue("downloadPathDir");
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDirChoiced,
                     (path.isEmpty() || !QFile::exists(path)) ? DownloadUtils::Core::downloadPrefix() : path);
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadDLoadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadDLoadLimit"));
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadULoadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadULoadLimit"));


    G_SETTING_PTR->setValue(DownloadSettingManager::SkinEffectLevelChoiced,
                     readXmlAttributeByTagNameValue("skinEffectLevel"));
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinFontChoiced,
                     readXmlAttributeByTagNameValue("skinFont").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionChoiced,
                     readXmlAttributeByTagNameValue("skinSuspension"));
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionPerChoiced,
                     readXmlAttributeByTagNameValue("skinSuspensionPer").toInt());

}
