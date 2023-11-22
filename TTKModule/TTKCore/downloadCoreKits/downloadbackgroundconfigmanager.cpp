#include "downloadbackgroundconfigmanager.h"

DownloadSkinConfigManager::DownloadSkinConfigManager()
    : TTKAbstractXml()
{

}

bool DownloadSkinConfigManager::readBuffer(DownloadSkinConfigItem &items)
{
    items.m_name = readAttributeByTagName("name");
    items.m_useCount = readAttributeByTagName("useCount").toInt();
    return true;
}

bool DownloadSkinConfigManager::writeBuffer(const DownloadSkinConfigItem &items)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot("TTKSkin");

    writeDomElement(rootDom, "creator", {"value", TTK_APP_NAME});
    writeDomElement(rootDom, "name", {"value", items.m_name});
    writeDomElement(rootDom, "useCount", {"value", items.m_useCount});

    save();
    return true;
}
