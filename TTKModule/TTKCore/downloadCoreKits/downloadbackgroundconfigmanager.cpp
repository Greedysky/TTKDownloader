#include "downloadbackgroundconfigmanager.h"

DownloadSkinConfigManager::DownloadSkinConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

bool DownloadSkinConfigManager::readBuffer(DownloadSkinConfigItem &items)
{
    items.m_name = readXmlAttributeByTagName("name");
    items.m_useCount = readXmlAttributeByTagName("useCount").toInt();
    return true;
}

bool DownloadSkinConfigManager::writeBuffer(const DownloadSkinConfigItem &items)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot("TTKSkin");

    writeDomElement(rootDom, "creator", TTKXmlAttribute("value", TTK_APP_NAME));
    writeDomElement(rootDom, "name", TTKXmlAttribute("value", items.m_name));
    writeDomElement(rootDom, "useCount", TTKXmlAttribute("value", items.m_useCount));

    save();
    return true;
}
