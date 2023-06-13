#include "downloadconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadcoreutils.h"

#include <QRect>

DownloadConfigManager::DownloadConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

void DownloadConfigManager::readBuffer() const
{
    G_SETTING_PTR->setValue(DownloadSettingManager::CloseEventMode, readXmlAttributeByTagName("closeEventMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::CloseNetWorkMode, readXmlAttributeByTagName("closeNetworkMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::FileAssociationMode, readXmlAttributeByTagName("fileAssociationMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpMode, readXmlAttributeByTagName("startUpMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpRunMode, readXmlAttributeByTagName("startUpRunMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::SlienceRunMode, readXmlAttributeByTagName("slienceRunMode").toInt());

    G_SETTING_PTR->setValue(DownloadSettingManager::BackgroundThemeValue, readXmlAttributeByTagName("backgroundThemeValue"));
    G_SETTING_PTR->setValue(DownloadSettingManager::BackgroundTransparent, readXmlAttributeByTagName("backgroundTransparent").toInt());

    G_SETTING_PTR->setValue(DownloadSettingManager::HotkeyEnable, readXmlAttributeByTagName("hotkeyEnable"));
    G_SETTING_PTR->setValue(DownloadSettingManager::HotkeyValue, readXmlAttributeByTagName("hotkeyValue"));

    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadLimit, readXmlAttributeByTagName("downloadLimit").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMode, readXmlAttributeByTagName("downloadMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMaxCount, readXmlAttributeByTagName("downloadMaxCount").toInt());

    const QString &path = readXmlAttributeByTagName("downloadPathDir");
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDir, (path.isEmpty() || !QFile::exists(path)) ? TTK::Core::downloadPrefix() : path);
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadDLoadLimit, readXmlAttributeByTagName("downloadDLoadLimit"));
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadULoadLimit, readXmlAttributeByTagName("downloadULoadLimit"));

    G_SETTING_PTR->setValue(DownloadSettingManager::SkinEffectLevel, readXmlAttributeByTagName("skinEffectLevel"));
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspension, readXmlAttributeByTagName("skinSuspension"));
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionValue, readXmlAttributeByTagName("skinSuspensionValue").toInt());
}

void DownloadConfigManager::writeBuffer()
{
    const QPoint &widgetPosition = G_SETTING_PTR->value(DownloadSettingManager::WidgetPosition).toPoint();
    const QSize &widgetSize = G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize();
    const int closeEventMode = G_SETTING_PTR->value(DownloadSettingManager::CloseEventMode).toInt();
    const int closeNetworkMode = G_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkMode).toInt();
    const int fileAssociationMode = G_SETTING_PTR->value(DownloadSettingManager::FileAssociationMode).toInt();
    const int startupMode = G_SETTING_PTR->value(DownloadSettingManager::StartUpMode).toInt();
    const int startupRunMode = G_SETTING_PTR->value(DownloadSettingManager::StartUpRunMode).toInt();
    const int slienceRunMode = G_SETTING_PTR->value(DownloadSettingManager::SlienceRunMode).toInt();

    const QString &backgroundThemeValue = G_SETTING_PTR->value(DownloadSettingManager::BackgroundThemeValue).toString();
    const int backgroundTransparent = G_SETTING_PTR->value(DownloadSettingManager::BackgroundTransparent).toInt();

    const int hotkeyEnable = G_SETTING_PTR->value(DownloadSettingManager::HotkeyEnable).toInt();
    const QString &hotkeyValue = G_SETTING_PTR->value(DownloadSettingManager::HotkeyValue).toString();

    const int downloadLimit = G_SETTING_PTR->value(DownloadSettingManager::DownloadLimit).toInt();
    const int downloadMode = G_SETTING_PTR->value(DownloadSettingManager::DownloadMode).toInt();
    const int downloadMaxCount = G_SETTING_PTR->value(DownloadSettingManager::DownloadMaxCount).toInt();
    const QString &downloadPathDir = G_SETTING_PTR->value(DownloadSettingManager::DownloadPathDir).toString();
    const QString &downloadDLoadLimit = G_SETTING_PTR->value(DownloadSettingManager::DownloadDLoadLimit).toString();
    const QString &downloadULoadLimit = G_SETTING_PTR->value(DownloadSettingManager::DownloadULoadLimit).toString();

    const int skinEffectLevel = G_SETTING_PTR->value(DownloadSettingManager::SkinEffectLevel).toInt();
    const int skinSuspension = G_SETTING_PTR->value(DownloadSettingManager::SkinSuspension).toInt();
    const int skinSuspensionValue = G_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionValue).toInt();

    if(!toFile(COFIG_PATH_FULL))
    {
        return;
    }

    createProcessingInstruction();
    QDomElement rootDom = createRoot(APP_NAME);
    QDomElement plusSettingDom = writeDomNode(rootDom, "plusSetting");
    QDomElement backgroundSettingDom = writeDomNode(rootDom, "backgroundSetting");
    QDomElement hotkeySettingDom = writeDomNode(rootDom, "hotkeySetting");
    QDomElement downloadSettingDom = writeDomNode(rootDom, "downloadSetting");
    QDomElement skinSettingDom = writeDomNode(rootDom, "skinSetting");

    writeDomElement(plusSettingDom, "geometry", TTKXmlAttribute("value", QString("%1,%2,%3,%4").arg(widgetPosition.x()).arg(widgetPosition.y()).arg(widgetSize.width()).arg(widgetSize.height())));
    writeDomElement(plusSettingDom, "closeEventMode", TTKXmlAttribute("value", closeEventMode));
    writeDomElement(plusSettingDom, "closeNetworkMode", TTKXmlAttribute("value", closeNetworkMode));
    writeDomElement(plusSettingDom, "fileAssociationMode", TTKXmlAttribute("value", fileAssociationMode));
    writeDomElement(plusSettingDom, "startUpMode", TTKXmlAttribute("value", startupMode));
    writeDomElement(plusSettingDom, "startUpRunMode", TTKXmlAttribute("value", startupRunMode));
    writeDomElement(plusSettingDom, "slienceRunMode", TTKXmlAttribute("value", slienceRunMode));

    writeDomElement(backgroundSettingDom, "backgroundThemeValue", TTKXmlAttribute("value", backgroundThemeValue));
    writeDomElement(backgroundSettingDom, "backgroundTransparent", TTKXmlAttribute("value", backgroundTransparent));

    writeDomElement(hotkeySettingDom, "hotkeyEnable", TTKXmlAttribute("value", hotkeyEnable));
    writeDomElement(hotkeySettingDom, "hotkeyValue", TTKXmlAttribute("value", hotkeyValue));

    writeDomElement(downloadSettingDom, "downloadLimit", TTKXmlAttribute("value", downloadLimit));
    writeDomElement(downloadSettingDom, "downloadMode", TTKXmlAttribute("value", downloadMode));
    writeDomElement(downloadSettingDom, "downloadMaxCount", TTKXmlAttribute("value", downloadMaxCount));
    writeDomElement(downloadSettingDom, "downloadPathDir", TTKXmlAttribute("value", downloadPathDir));
    writeDomElement(downloadSettingDom, "downloadDLoadLimit", TTKXmlAttribute("value", downloadDLoadLimit));
    writeDomElement(downloadSettingDom, "downloadULoadLimit", TTKXmlAttribute("value", downloadULoadLimit));

    writeDomElement(skinSettingDom, "skinEffectLevel", TTKXmlAttribute("value", skinEffectLevel));
    writeDomElement(skinSettingDom, "skinSuspension", TTKXmlAttribute("value", skinSuspension));
    writeDomElement(skinSettingDom, "skinSuspensionValue", TTKXmlAttribute("value", skinSuspensionValue));

    QTextStream out(m_file);
    m_document->save(out, 4);
}

QRect DownloadConfigManager::readWindowGeometry() const
{
    const QDomNodeList &nodes = m_document->elementsByTagName("geometry");
    if(nodes.isEmpty())
    {
        return QRect(0, 0, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    }

    const QDomElement &element = nodes.item(0).toElement();
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
