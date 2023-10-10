#include "downloadbackgroundconfigmanager.h"

DownloadSkinConfigManager::DownloadSkinConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

void DownloadSkinConfigManager::readBuffer(DownloadSkinConfigItem &item)
{
    item.m_name = readXmlAttributeByTagName("name");
    item.m_useCount = readXmlAttributeByTagName("useCount").toInt();
}

void DownloadSkinConfigManager::writeBuffer(const DownloadSkinConfigItem &item)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot("TTKSkin");

    writeDomElement(rootDom, "creator", TTKXmlAttribute("value", TTK_APP_NAME));
    writeDomElement(rootDom, "name", TTKXmlAttribute("value", item.m_name));
    writeDomElement(rootDom, "useCount", TTKXmlAttribute("value", item.m_useCount));

    save();
}
