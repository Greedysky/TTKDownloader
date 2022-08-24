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
    QPoint widgetPositionChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::WidgetPosition).toPoint();
    QSize widgetSizeChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::WidgetSize).toSize();
    int closeEventChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::CloseEventChoiced).toInt();
    int closeNetWorkChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::CloseNetWorkChoiced).toInt();
    int fileAssociationChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::FileAssociationChoiced).toInt();
    int startupModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::StartUpModeChoiced).toInt();
    int startupRunModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::StartUpRunModeChoiced).toInt();
    int slienceRunModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::SlienceRunModeChoiced).toInt();

    QString bgThemeChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::BgThemeChoiced).toString();
    int bgTransparentChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::BgTransparentChoiced).toInt();

    int downloadLimit = G_SETTING_PTR->value(DownloadSettingManager::Config::DownloadLimitChoiced).toInt();
    int downloadModeChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::DownloadModeChoiced).toInt();
    int downloadMaxCountChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::DownloadMaxCountChoiced).toInt();
    QString downloadPathDir = G_SETTING_PTR->value(DownloadSettingManager::Config::DownloadPathDirChoiced).toString();
    QString downloadDLoadLimit = G_SETTING_PTR->value(DownloadSettingManager::Config::DownloadDLoadLimitChoiced).toString();
    QString downloadULoadLimit = G_SETTING_PTR->value(DownloadSettingManager::Config::DownloadULoadLimitChoiced).toString();

    int skinEffectLevelChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::SkinEffectLevelChoiced).toInt();
    int skinFontChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::SkinFontChoiced).toInt();
    int skinSuspensionChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::SkinSuspensionChoiced).toInt();
    int skinSuspensionPerChoiced = G_SETTING_PTR->value(DownloadSettingManager::Config::SkinSuspensionPerChoiced).toInt();

    if(!writeConfig(COFIG_PATH_FULL))
    {
        return;
    }

    createProcessingInstruction();
    QDomElement rootDom = createRoot(APP_NAME);
    QDomElement plusSettingDom = writeDomNode(rootDom, "plusSetting");
    QDomElement backgroundSettingDom = writeDomNode(rootDom, "backgroundSetting");
    QDomElement downloadSettingDom = writeDomNode(rootDom, "downloadSetting");
    QDomElement skinSettingDom = writeDomNode(rootDom, "skinSetting");

    writeDomElement(plusSettingDom, "geometry", DownloadXmlAttribute("value", QString("%1,%2,%3,%4").arg(widgetPositionChoiced.x())
                    .arg(widgetPositionChoiced.y()).arg(widgetSizeChoiced.width()).arg(widgetSizeChoiced.height())));
    writeDomElement(plusSettingDom, "closeEvent", DownloadXmlAttribute("value", closeEventChoiced));
    writeDomElement(plusSettingDom, "closeNetwork", DownloadXmlAttribute("value", closeNetWorkChoiced));
    writeDomElement(plusSettingDom, "fileAssociation", DownloadXmlAttribute("value", fileAssociationChoiced));
    writeDomElement(plusSettingDom, "startUpMode", DownloadXmlAttribute("value", startupModeChoiced));
    writeDomElement(plusSettingDom, "startUpRunMode", DownloadXmlAttribute("value", startupRunModeChoiced));
    writeDomElement(plusSettingDom, "slienceRunMode", DownloadXmlAttribute("value", slienceRunModeChoiced));

    writeDomElement(backgroundSettingDom, "bgTheme", DownloadXmlAttribute("value", bgThemeChoiced));
    writeDomElement(backgroundSettingDom, "bgTransparent", DownloadXmlAttribute("value", bgTransparentChoiced));

    writeDomElement(downloadSettingDom, "downloadLimit", DownloadXmlAttribute("value", downloadLimit));
    writeDomElement(downloadSettingDom, "downloadMode", DownloadXmlAttribute("value", downloadModeChoiced));
    writeDomElement(downloadSettingDom, "downloadMaxCount", DownloadXmlAttribute("value", downloadMaxCountChoiced));
    writeDomElement(downloadSettingDom, "downloadPathDir", DownloadXmlAttribute("value", downloadPathDir));
    writeDomElement(downloadSettingDom, "downloadDLoadLimit", DownloadXmlAttribute("value", downloadDLoadLimit));
    writeDomElement(downloadSettingDom, "downloadULoadLimit", DownloadXmlAttribute("value", downloadULoadLimit));

    writeDomElement(skinSettingDom, "skinEffectLevel", DownloadXmlAttribute("value", skinEffectLevelChoiced));
    writeDomElement(skinSettingDom, "skinFont", DownloadXmlAttribute("value", skinFontChoiced));
    writeDomElement(skinSettingDom, "skinSuspension", DownloadXmlAttribute("value", skinSuspensionChoiced));
    writeDomElement(skinSettingDom, "skinSuspensionPer", DownloadXmlAttribute("value", skinSuspensionPerChoiced));

    QTextStream out(m_file);
    m_document->save(out, 4);
}

QRect DownloadSysConfigManager::readWindowGeometry() const
{
    const QDomNodeList &nodelist = m_document->elementsByTagName("geometry");
    if(nodelist.isEmpty())
    {
        return QRect(0, 0, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    }

    const QDomElement &element = nodelist.at(0).toElement();
    const QStringList &list = element.attribute("value").split(",");
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
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::CloseEventChoiced,
                     readXmlAttributeByTagNameValue("closeEvent").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::CloseNetWorkChoiced,
                     readXmlAttributeByTagNameValue("closeNetwork").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::FileAssociationChoiced,
                     readXmlAttributeByTagNameValue("fileAssociation").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::StartUpModeChoiced,
                     readXmlAttributeByTagNameValue("startUpMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::StartUpRunModeChoiced,
                     readXmlAttributeByTagNameValue("startUpRunMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::SlienceRunModeChoiced,
                     readXmlAttributeByTagNameValue("slienceRunMode").toInt());


    G_SETTING_PTR->setValue(DownloadSettingManager::Config::BgThemeChoiced,
                     readXmlAttributeByTagNameValue("bgTheme"));
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::BgTransparentChoiced,
                     readXmlAttributeByTagNameValue("bgTransparent").toInt());


    G_SETTING_PTR->setValue(DownloadSettingManager::Config::DownloadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadLimit").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::DownloadModeChoiced,
                     readXmlAttributeByTagNameValue("downloadMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::DownloadMaxCountChoiced,
                     readXmlAttributeByTagNameValue("downloadMaxCount").toInt());
    const QString &path = readXmlAttributeByTagNameValue("downloadPathDir");
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::DownloadPathDirChoiced,
                     (path.isEmpty() || !QFile::exists(path)) ? DownloadUtils::Core::downloadPrefix() : path);
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::DownloadDLoadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadDLoadLimit"));
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::DownloadULoadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadULoadLimit"));


    G_SETTING_PTR->setValue(DownloadSettingManager::Config::SkinEffectLevelChoiced,
                     readXmlAttributeByTagNameValue("skinEffectLevel"));
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::SkinFontChoiced,
                     readXmlAttributeByTagNameValue("skinFont").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::SkinSuspensionChoiced,
                     readXmlAttributeByTagNameValue("skinSuspension"));
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::SkinSuspensionPerChoiced,
                     readXmlAttributeByTagNameValue("skinSuspensionPer").toInt());

}
