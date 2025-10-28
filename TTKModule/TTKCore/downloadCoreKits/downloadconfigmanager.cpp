#include "downloadconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadstringutils.h"

#include <QRect>

DownloadConfigManager::DownloadConfigManager()
    : TTKAbstractXml()
{

}

bool DownloadConfigManager::readBuffer()
{
    int items = 0;
    return readBuffer(items);
}

bool DownloadConfigManager::writeBuffer()
{
    int items = 0;
    return writeBuffer(items);
}

bool DownloadConfigManager::readBuffer(int &items)
{
    Q_UNUSED(items);

    G_SETTING_PTR->setValue(DownloadSettingManager::CloseEventMode, readAttributeByTagName("closeEventMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpMode, readAttributeByTagName("startUpMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpRunMode, readAttributeByTagName("startUpRunMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::SlienceRunMode, readAttributeByTagName("slienceRunMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::LogTrackEnable, readAttributeByTagName("logTrackEnable").toInt());

    G_SETTING_PTR->setValue(DownloadSettingManager::BackgroundThemeValue, readAttributeByTagName("backgroundThemeValue"));
    G_SETTING_PTR->setValue(DownloadSettingManager::BackgroundTransparent, readAttributeByTagName("backgroundTransparent").toInt());

    G_SETTING_PTR->setValue(DownloadSettingManager::HotkeyEnable, readAttributeByTagName("hotkeyEnable"));
    G_SETTING_PTR->setValue(DownloadSettingManager::HotkeyValue, readAttributeByTagName("hotkeyValue"));

    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadLimit, readAttributeByTagName("downloadLimit").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMode, readAttributeByTagName("downloadMode").toInt());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMaxCount, readAttributeByTagName("downloadMaxCount").toInt());

    const QString &path = readAttributeByTagName("downloadPathDir");
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDir, (path.isEmpty() || !QFile::exists(path)) ? TTK::String::downloadPrefix() : path);
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadDLoadLimit, readAttributeByTagName("downloadDLoadLimit"));
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadULoadLimit, readAttributeByTagName("downloadULoadLimit"));

    G_SETTING_PTR->setValue(DownloadSettingManager::SkinEffectLevel, readAttributeByTagName("skinEffectLevel"));
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspension, readAttributeByTagName("skinSuspension"));
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionValue, readAttributeByTagName("skinSuspensionValue").toInt());
    return true;
}

bool DownloadConfigManager::writeBuffer(const int &items)
{
    Q_UNUSED(items);

    const QPoint &widgetPosition = G_SETTING_PTR->value(DownloadSettingManager::WidgetPosition).toPoint();
    const QSize &widgetSize = G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize();
    const int closeEventMode = G_SETTING_PTR->value(DownloadSettingManager::CloseEventMode).toInt();
    const int startupMode = G_SETTING_PTR->value(DownloadSettingManager::StartUpMode).toInt();
    const int startupRunMode = G_SETTING_PTR->value(DownloadSettingManager::StartUpRunMode).toInt();
    const int slienceRunMode = G_SETTING_PTR->value(DownloadSettingManager::SlienceRunMode).toInt();
    const int logTrackEnable = G_SETTING_PTR->value(DownloadSettingManager::LogTrackEnable).toInt();

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

    createProcessingInstruction();
    QDomElement rootDom = createRoot(TTK_APP_NAME);
    QDomElement plusSettingDom = writeDomElement(rootDom, "plusSetting");
    QDomElement backgroundSettingDom = writeDomElement(rootDom, "backgroundSetting");
    QDomElement hotkeySettingDom = writeDomElement(rootDom, "hotkeySetting");
    QDomElement downloadSettingDom = writeDomElement(rootDom, "downloadSetting");
    QDomElement skinSettingDom = writeDomElement(rootDom, "skinSetting");

    writeDomElement(plusSettingDom, "geometry", {"value", QString("%1,%2,%3,%4").arg(widgetPosition.x()).arg(widgetPosition.y()).arg(widgetSize.width()).arg(widgetSize.height())});
    writeDomElement(plusSettingDom, "closeEventMode", {"value", closeEventMode});
    writeDomElement(plusSettingDom, "startUpMode", {"value", startupMode});
    writeDomElement(plusSettingDom, "startUpRunMode", {"value", startupRunMode});
    writeDomElement(plusSettingDom, "slienceRunMode", {"value", slienceRunMode});
    writeDomElement(plusSettingDom, "logTrackEnable", {"value", logTrackEnable});

    writeDomElement(backgroundSettingDom, "backgroundThemeValue", {"value", backgroundThemeValue});
    writeDomElement(backgroundSettingDom, "backgroundTransparent", {"value", backgroundTransparent});

    writeDomElement(hotkeySettingDom, "hotkeyEnable", {"value", hotkeyEnable});
    writeDomElement(hotkeySettingDom, "hotkeyValue", {"value", hotkeyValue});

    writeDomElement(downloadSettingDom, "downloadLimit", {"value", downloadLimit});
    writeDomElement(downloadSettingDom, "downloadMode", {"value", downloadMode});
    writeDomElement(downloadSettingDom, "downloadMaxCount", {"value", downloadMaxCount});
    writeDomElement(downloadSettingDom, "downloadPathDir", {"value", downloadPathDir});
    writeDomElement(downloadSettingDom, "downloadDLoadLimit", {"value", downloadDLoadLimit});
    writeDomElement(downloadSettingDom, "downloadULoadLimit", {"value", downloadULoadLimit});

    writeDomElement(skinSettingDom, "skinEffectLevel", {"value", skinEffectLevel});
    writeDomElement(skinSettingDom, "skinSuspension", {"value", skinSuspension});
    writeDomElement(skinSettingDom, "skinSuspensionValue", {"value", skinSuspensionValue});

    save();
    return true;
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
