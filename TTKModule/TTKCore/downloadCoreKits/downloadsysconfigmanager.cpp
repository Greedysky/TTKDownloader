#include "downloadsysconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadcoreutils.h"

#include <QRect>

DownloadSysConfigManager::DownloadSysConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

QString DownloadSysConfigManager::getClassName()
{
    return staticMetaObject.className();
}

void DownloadSysConfigManager::writeXMLConfig()
{
    QPoint widgetPositionChoiced = M_SETTING_PTR->value(DownloadSettingManager::WidgetPosition).toPoint();
    QSize widgetSizeChoiced = M_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize();
    int closeEventChoiced = M_SETTING_PTR->value(DownloadSettingManager::CloseEventChoiced).toInt();
    int closeNetWorkChoiced = M_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkChoiced).toInt();
    int fileAssociationChoiced = M_SETTING_PTR->value(DownloadSettingManager::FileAssociationChoiced).toInt();
    int windowQuitModeChoiced = M_SETTING_PTR->value(DownloadSettingManager::WindowQuitModeChoiced).toInt();

    ///////////////////////////////////////////////////////////////////////////
    QString bgThemeChoiced = M_SETTING_PTR->value(DownloadSettingManager::BgThemeChoiced).toString();
    int bgTransparentChoiced = M_SETTING_PTR->value(DownloadSettingManager::BgTransparentChoiced).toInt();

    ///////////////////////////////////////////////////////////////////////////
    int downloadLimit = M_SETTING_PTR->value(DownloadSettingManager::DownloadLimitChoiced).toInt();
    QString downloadPathDir = M_SETTING_PTR->value(DownloadSettingManager::DownloadPathDirChoiced).toString();
    QString downloadDLoadLimit = M_SETTING_PTR->value(DownloadSettingManager::DownloadDLoadLimitChoiced).toString();
    QString downloadULoadLimit = M_SETTING_PTR->value(DownloadSettingManager::DownloadULoadLimitChoiced).toString();
    ///////////////////////////////////////////////////////////////////////////

    //Open wirte file
    if( !writeConfig(COFIGPATH_FULL) )
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement playerDom = createRoot(APPNAME);
    //Class A
    QDomElement plusSettingDom = writeDom(playerDom, "plusSetting");
    QDomElement backgroundSettingDom = writeDom(playerDom, "backgroundSetting");
    QDomElement downloadSettingDom = writeDom(playerDom, "downloadSetting");
    //Class B

    ///////////////////////////////////////////////////////////////////////////
    writeDomElement(plusSettingDom, "geometry", DownloadXmlAttribute("value", QString("%1,%2,%3,%4").arg(widgetPositionChoiced.x())
                    .arg(widgetPositionChoiced.y()).arg(widgetSizeChoiced.width()).arg(widgetSizeChoiced.height())));
    writeDomElement(plusSettingDom, "closeEvent", DownloadXmlAttribute("value", closeEventChoiced));
    writeDomElement(plusSettingDom, "closeNetwork", DownloadXmlAttribute("value", closeNetWorkChoiced));
    writeDomElement(plusSettingDom, "fileAssociation", DownloadXmlAttribute("value", fileAssociationChoiced));
    writeDomElement(plusSettingDom, "windowQuitMode", DownloadXmlAttribute("value", windowQuitModeChoiced));

    ///////////////////////////////////////////////////////////////////////////
    writeDomElement(backgroundSettingDom, "bgTheme", DownloadXmlAttribute("value", bgThemeChoiced));
    writeDomElement(backgroundSettingDom, "bgTransparent", DownloadXmlAttribute("value", bgTransparentChoiced));

    ///////////////////////////////////////////////
    writeDomElement(downloadSettingDom, "downloadLimit", DownloadXmlAttribute("value", downloadLimit));
    writeDomElement(downloadSettingDom, "downloadPathDir", DownloadXmlAttribute("value", downloadPathDir));
    writeDomElement(downloadSettingDom, "downloadDLoadLimit", DownloadXmlAttribute("value", downloadDLoadLimit));
    writeDomElement(downloadSettingDom, "downloadULoadLimit", DownloadXmlAttribute("value", downloadULoadLimit));

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
    QStringList lists = element.attribute("value").split(",");
    if(lists.count() == 4)
    {
        return QRect(lists[0].toInt() < 0 ? 0 : lists[0].toInt(),
                     lists[1].toInt() < 0 ? 0 : lists[1].toInt(),
                     lists[2].toInt(), lists[3].toInt());
    }
    else
    {
        return QRect(0, 0, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    }
}

void DownloadSysConfigManager::readSysLoadConfig() const
{
    M_SETTING_PTR->setValue(DownloadSettingManager::CloseEventChoiced,
                     readXmlAttributeByTagNameValue("closeEvent").toInt());
    M_SETTING_PTR->setValue(DownloadSettingManager::CloseNetWorkChoiced,
                     readXmlAttributeByTagNameValue("closeNetwork").toInt());
    M_SETTING_PTR->setValue(DownloadSettingManager::FileAssociationChoiced,
                     readXmlAttributeByTagNameValue("fileAssociation").toInt());
    M_SETTING_PTR->setValue(DownloadSettingManager::WindowQuitModeChoiced,
                     readXmlAttributeByTagNameValue("windowQuitMode").toInt());


    M_SETTING_PTR->setValue(DownloadSettingManager::BgThemeChoiced,
                     readXmlAttributeByTagNameValue("bgTheme"));
    M_SETTING_PTR->setValue(DownloadSettingManager::BgTransparentChoiced,
                     readXmlAttributeByTagNameValue("bgTransparent").toInt());


    M_SETTING_PTR->setValue(DownloadSettingManager::DownloadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadLimit").toInt());
    QString path = readXmlAttributeByTagNameValue("downloadPathDir");
    M_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDirChoiced,
                     (path.isEmpty() || !QFile::exists(path)) ? DownloadUtils::Core::downloadPrefix() : path);
    M_SETTING_PTR->setValue(DownloadSettingManager::DownloadDLoadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadDLoadLimit"));
    M_SETTING_PTR->setValue(DownloadSettingManager::DownloadULoadLimitChoiced,
                     readXmlAttributeByTagNameValue("downloadULoadLimit"));
}
